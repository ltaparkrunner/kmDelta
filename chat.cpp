#include "chat.h"

chat::chat():
    prb({ {{false, 500}, {false, 500}, {false, 500}, {false, 500}} , {{0, -273}, {0, -2648}, {0, -711}, {0, -1910}, {0, -845}, {0, -1519}, {0, -1736}, {0, -1612}}} )
  , T_Date("")
  , minute(0)
  , status_control ("")
  , lvm ({false, ""})
  , CheckSum(0)
{
//    QObject::connect(&probePollTmr, &QTimer::timeout, this, &ControlIp::periodReq);
}

ret_t chat::get_tcp_chatdata_bArray(){ // message to respond params from device
    const char data[12] = {1, 1, 0,0,0,6,33,3,0,0,0,16};
    QByteArray *bdt = new QByteArray(data, 12);
    return {2,bdt};
}

int chat::get_tcp_chatdata(MbtcpClient* tcpC){
    ret_t rez = get_tcp_chatdata_bArray();
    if(rez.res < 0) return -1;
    else if(tcpC->sendToTcp(rez.bdata) > 0) {
        qDebug("success /n");
        // тут разбор и запись в configs -> parms
        return 0;
    }
    else return -2;
}

QList<qint32>* chat::get_tcp_chatdata_resp(MbtcpClient* tcpC) {
    QByteArray dt = tcpC->getAll();
    int nr = 9;//9 - начало данных
    for (int i = 0; i < 8; i++)
    {
//        if (i == 2)
//        { }
        uint d = (uint)(dt[nr]);
        d = d << 8; nr++;
        d = d | dt[nr]; nr++;
        int16_t id = (int16_t)d;
        if (d == 0x8000) { prb.vl[i].absolutnoe = -20000; }
        else
        {
            double dd = id / 2.0;
            prb.vl[i].absolutnoe = dd;
        }
    }

    if ( 0 != dt[32] ) { prb.glh[1].alarm = true; prb.glh[1].value = dt[32]; }
    else { prb.glh[1].alarm = false; prb.glh[1].value = 0; }
    if ( 0 != dt[33] ) { prb.glh[2].alarm = true; prb.glh[2].value = dt[33]; }
    else { prb.glh[2].alarm = false; prb.glh[2].value = 0; }//Неисправность МКЛП
    if ( 0 != dt[34] ) { prb.glh[3].alarm = true; prb.glh[3].value = dt[34]; }
    else { prb.glh[3].alarm = false; prb.glh[3].value = 0; }//Нет_связи_с МКЛП

    if ( 0 != dt[28] && 0 != dt[29] )///Дата и время
    {
        QString x[5];
        for (short h = 0; h < 5; h++) {
            x[h] = QString::number(dt[25 + h], 16);
            if (x[h].length() == 1) x[h] = "0" + x[h];
        }
        T_Date = x[2] + ":" + x[1] + ":" + x[0] + " " + x[3] + "." + x[4] + ".20" + QString::number(dt[30], 16);
    }

    minute = (dt[35] << 8) + dt[36];
    lvm.Visible = true;
    if (1 == dt[38])
    {
        status_control = "Алгоритм текущего мониторинга мёртвого нуля: ";
    }
    if (3 == dt[38])
    {
        status_control = "Алгоритм калибровки: ";
    }


    if (CheckSum != 0)
        lvm.Text = " Версия: " + QString::number(dt[40]) + "CRC32: " + QString::number(CheckSum, 16) + ")";
    else
        lvm.Text = " Версия: " + QString::number(dt[40]);
    QList<qint32>* rt = new QList<qint32>();
    for(int i = 0; i<8; i++)
        rt->append(prb.vl[i].absolutnoe);
    return rt;
}
