#include "configs.h"
#include "crc32.h"
#include "mbtcpClient.h"
#include <QFile>
#include <QTextStream>

parms::parms():
    otnositelnoe_otobragenie( 0 )
    ,inversion_data(true)
    ,inversion_dt (false)
    ,avariya({{1,420,560,1},{0,380,720,1},{0,0,0,0},{0,0,0,0}})
    ,porog_max (420)
    ,porog_min (560)
    ,timeout_alarm (2)
    ,version_proshivki (0)
    ,alarmt (4)
    ,ethIP ("192.168.1.80")
//    ,IP1 ("192.168.1.170")
    ,ethIP_new ("192.168.1.170")
    ,ethMASK ("255.255.0.0")
    ,ethMASK_new ("255.255.0.0")
    ,ethPORT ("502")
    ,ethPORT_new ("503")
 //   ,data ({{0, -273.5}, {0, -2648.5}, {0, -711.5}, {0, -1910.5}, {0, -845.5}, {0, -1519.5}, {0, -1736.0}, {0, -1612.0}})
    ,data ({{0, -273}, {0, -2648}, {0, -711}, {0, -1910}, {0, -845}, {0, -1519}, {0, -1736}, {0, -1612}})
    ,mashtab (10)
    ,graph_memory (100)
    ,obnovlenie_proshivki (false)
{ }

configs::configs(MbtcpClient* tcpe):
//    ,cnfg(0)
    tcpC(tcpe)
    ,cnfg(parms())
{ }

int configs::save_file_configs(QString filen) {

    QFile cfile(filen);
    if (!cfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return -1;
    QTextStream wr(&cfile);
//    using (StreamWriter wr = new StreamWriter(sf, false))
    {
        wr << "IP-адрес ПТК КМ-Дельта:" + cnfg.ethIP << "\n";
        wr << "Маска подсети:" + cnfg.ethMASK << "\n";
        wr << "Удалённый IP:" + cnfg.ethIP << "\n";
        wr << "Порт ПТК КМ-Дельта:" + cnfg.ethPORT << "\n";
//        wr << "Порт программы:" + gl.SPORT << "\n";
        wr << "Задержка срабатывания сигнализации:" + QString::number(cnfg.timeout_alarm) << "\n";
        wr << "Масштаб отображения, с:" + QString::number(cnfg.mashtab) << "\n";
        wr << "Отображение относительных данных:" + QString::number(cnfg.otnositelnoe_otobragenie) << "\n";
        wr << "Смещение канала 1, мкм:" + QString::number(cnfg.data[0].smeshenie) << "\n";
        wr << "Смещение канала 2, мкм:" + QString::number(cnfg.data[1].smeshenie) << "\n";
        wr << "Смещение канала 3, мкм:" + QString::number(cnfg.data[2].smeshenie) << "\n";
        wr << "Смещение канала 4, мкм:" + QString::number(cnfg.data[3].smeshenie) << "\n";
        wr << "Смещение канала 5, мкм:" + QString::number(cnfg.data[4].smeshenie) << "\n";
        wr << "Смещение канала 6, мкм:" + QString::number(cnfg.data[5].smeshenie) << "\n";
        wr << "Смещение канала 7, мкм:" + QString::number(cnfg.data[6].smeshenie) << "\n";
        wr << "Смещение канала 8, мкм:" + QString::number(cnfg.data[7].smeshenie) << "\n";
        for (int i = 0; i < 4; i++)
        {
            QString str = "Реле " + QString::number(i + 1) + " верхний порог: "; wr << str + QString::number(cnfg.avariya[i].porog_max) << "\n";
            str = "Реле " + QString::number(i + 1) + " нижний порог: "; wr << str + QString::number(cnfg.avariya[i].porog_min) << "\n";
            str = "Реле " + QString::number(i + 1) + " аварийные датчики: "; wr << str + QString::number(cnfg.avariya[i].kolvo_avariynih_datchikov) << "\n";
            str = "Реле " + QString::number(i + 1) + " признак сигнализации: "; wr << str + QString::number(cnfg.avariya[i].avariya1_predupregdenie0) << "\n";
        }
        wr << "Максимум шкалы:" + QString::number(cnfg.porog_max) << "\n";
        wr << "Минимум шкалы:" + QString::number(cnfg.porog_min) << "\n";
        wr << "Инверсия данных:" + QString::number(cnfg.inversion_data) << "\n";
        //wr.WriteLine("Отключение реле:" + GL.otkl_panel.ToString());
        //wr.WriteLine("Сброс датчиков:" + GL.sensorReset.ToString());
        wr << "Память, точек:" + QString::number(cnfg.graph_memory) << "\n";
        wr << "Версия прошивки:" + QString::number(cnfg.version_proshivki) << "\n";
        wr << "Time_sec:" + QString::number(cnfg.alarmt) << "\n";
//        wr.Close();
        cfile.close();
    }
    return 0;
}
int configs::load_file_configs(QString filen) {
    QFile cfile(filen);
    if (!cfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return -1;
    QTextStream rd(&cfile);
    {
        QString str = rd.readLine(); int ind = str.indexOf(':'); ind++; cnfg.ethIP = str.mid(ind, str.length() - ind);
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.ethMASK = str.mid(ind, str.length() - ind);
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.ethIP = str.mid(ind, str.length() - ind);
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.ethPORT = str.mid(ind, str.length() - ind);
//        str = rd.readLine(); ind = str.indexOf(':'); ind++; gl.SPORT = (str.mid(ind, str.length() - ind)).toInt();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.timeout_alarm = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.mashtab = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.otnositelnoe_otobragenie = (str.mid(ind, str.length() - ind) == QString("true"));
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.data[0].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.data[1].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.data[2].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.data[3].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.data[4].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.data[5].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.data[6].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.data[7].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
        for (int i = 0; i < 4; i++)
        {
            str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.avariya[i].porog_max = (str.mid(ind, str.length() - ind)).toInt();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.avariya[i].porog_min = (str.mid(ind, str.length() - ind)).toInt();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.avariya[i].kolvo_avariynih_datchikov = (str.mid(ind, str.length() - ind)).toInt();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.avariya[i].avariya1_predupregdenie0 = (str.mid(ind, str.length() - ind)).toInt();
        }
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.porog_max = (str.mid(ind, str.length() - ind)).toShort();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.porog_min = (str.mid(ind, str.length() - ind)).toShort();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.inversion_data = (str.mid(ind, str.length() - ind)== QString("true"));
        //str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; gl.otkl_panel = Convert.ToBoolean(str.Substring(ind, str.Length - ind));
        //GL.sensorReset = true;                     str = rd.ReadLine();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.graph_memory = (str.mid(ind, str.length() - ind)).toInt();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.version_proshivki = (str.mid(ind, str.length() - ind)).toUShort();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.alarmt = (str.mid(ind, str.length() - ind)).toShort();
    }
    cfile.close();
    return 0;
}

bool configs::check_IP(uint8_t ip[], QString& ip_s){
    if (ip_s.count('.') < 3) return false;
    auto i = ip_s.split('.').begin();
    for(int i1 = 0; i1 < 4; i1++){
        uint8_t t1 = (*i).toShort();
        ip[i1] = t1;
    }
    return true;
}

//bool configs::check_MASK(uint8_t ip[]){
//    if (cnfg.ethIP.count('.') < 3) return false;
//    auto i = cnfg.ethIP.split('.').begin();
//    for(int i1 = 0; i1 < 4; i1++){
//        uint8_t t1 = (*i).toShort();
//        ip[i1] = t1;
//    }
//    return true;
//}

ret_t configs::save_eth_configs_bArray() // save to device
{
    const int pr = 10;
    QByteArray *bdata = new QByteArray(61 + pr + 1, 0);
    QByteArray& bdt = *bdata;
//    bdt.resize(61 + pr + 1);
//    QByteArray *bdata = new QByteArray(61 + pr + 1);
//    try
    {
//        QByteArray &bdt = *bdata;
        int i;
        bdt[0] = 'G';   //Идификатор транзакции
        bdt[1] = 'B';   //Идификатор транзакции
        bdt[2] = 0;     //Идификатор протокола
        bdt[3] = 0;     //Идификатор протокола
        bdt[4] = 0;     //Длина
        bdt[5] = 0x3E;  //Длина
        bdt[6] = 'A';   //Адрес
        bdt[7] = 0x10;  //Функциональный код
        bdt[8] = 0;     //Адрес первого регистра
        bdt[9] = 0x33;  //Адрес первого регистра
        bdt[10] = 0;

        char tbdata = 0;
        if (cnfg.otnositelnoe_otobragenie == true) { tbdata = 1; } else { tbdata = 0; }
        if (cnfg.inversion_data == true) { tbdata += 0x02; }
        //if (GL.otkl_panel == true) { bdata[1 + pr] += 0x04; }
        //if (GL.sensorReset == true) { bdata[1 + pr] += 0x08; }
        if (cnfg.avariya[0].avariya1_predupregdenie0 == 1) { tbdata += 0x10; }//avariya1_predupregdenie0 == 1, когда выбран тип "Авария"
        if (cnfg.avariya[1].avariya1_predupregdenie0 == 1) { tbdata += 0x20; }
        if (cnfg.avariya[2].avariya1_predupregdenie0 == 1) { tbdata += 0x40; }
        if (cnfg.avariya[3].avariya1_predupregdenie0 == 1) { tbdata += 0x80; }
        bdt[1 + pr] = tbdata;
        uint16_t time = cnfg.timeout_alarm;
        bdt[3 + pr] = static_cast<uchar>(time); //time = Convert.ToUInt16(time >> 8);
        bdt[2 + pr] = static_cast<uchar>(time>>8);

        uint8_t ip[4];
        if (!check_IP(ip, cnfg.ethIP)) { return {1, bdata}; }
        for (i = 0; i < n_avar; i++) { bdt[i + 4 + pr] = ip[i]; }
        // maska
        //flag = string_to_ip(text_maska_new.Text, ref ip, 2);
        if (!check_IP(ip, cnfg.ethMASK)) { return {1, bdata}; }
        for (i = 0; i < n_avar; i++) { bdt[i + 8 + pr] = ip[i]; }

        //int sp = Convert.ToInt32(text_sport_new.Text);
        uint16_t dp = cnfg.ethPORT_new.toShort();
        //bdata[17 + pr] = (byte)(sp & 0x00FF);
        //bdata[16 + pr] = (byte)((sp >> 8) & 0x00FF);
        bdt[19 + pr] = static_cast<uint8_t>(dp & 0x00FF);
        bdt[18 + pr] = static_cast<uint8_t>((dp >> 8) & 0x00FF);

        int smechenie = 20;
        for (i = 0; i < n_dat; i++)
        {
            double dd = cnfg.data[i].smeshenie * 2.0;
            int idd = static_cast<uint16_t>(dd);
            bdt[smechenie + pr] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
            bdt[smechenie + pr] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
        }
        int ipr = cnfg.porog_max;
        bdt[37 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdt[36 + pr] = static_cast<uint8_t>(ipr & 0x00FF);

        ipr = cnfg.porog_min;
        bdt[39 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdt[38 + pr] = static_cast<uint8_t>(ipr & 0x00FF);


        bdt[40 + pr] = static_cast<uint8_t>((((cnfg.avariya[0].kolvo_avariynih_datchikov << 4) & 0xF0) | (cnfg.avariya[1].kolvo_avariynih_datchikov & 0x0F)));
        bdt[41 + pr] = static_cast<uint8_t>((((cnfg.avariya[2].kolvo_avariynih_datchikov << 4) & 0xF0) | (cnfg.avariya[3].kolvo_avariynih_datchikov & 0x0F)));

        smechenie = 42;
        for (i = 0; i < n_avar; i++)
        {
            int idd = cnfg.avariya[i].porog_max;
            bdt[smechenie + pr] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
            bdt[smechenie + pr] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
            idd = cnfg.avariya[i].porog_min;
            bdt[smechenie + pr] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
            bdt[smechenie + pr] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
        }
        QByteArray crc = bdt; //[] = new byte[58 + pr];

        uint32_t crc_f = crc32(crc, crc.length());
//        crc32(crc, crc.length());
        cnfg.version_proshivki = Crc16(crc, 58 + pr);
        ipr = cnfg.version_proshivki;
        bdt[59 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdt[58 + pr] = static_cast<uint8_t>(ipr & 0x00FF);

        // ////////////////////////////////////////
        ipr = cnfg.alarmt;
        bdt[60 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdt[61 + pr] = static_cast<uint8_t>(ipr & 0x00FF);

        // ////////////////////////////////////////
        return {2, bdata};
    }
    return {2, bdata};
}

int configs::save_eth_configs(tcpIntrfc *cl) {   // save to device
    tcpC->setReadyRead_saveDev(cl);
    ret_t rez = save_eth_configs_bArray();
    if(rez.res < 0) return -1;
    else if(tcpC->sendToTcp(rez.bdata) > 0) {
        qDebug("success /n");
        return 0;
    }
    else return -2;
}
int configs::save_eth_configs_resp() { // respond after save to device
    QByteArray ba = tcpC->getAll();
    if (ba[1] == 'O' && ba[2] == 'K' && ba[3] == '!')  // successfully save to device
        return 0;
    else if (ba == nullptr) return -2;
    else return -1;
}

ret_t configs::load_eth_configs_bArray(){ // message to respond params from device
    const char data[12] = {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0};
    QByteArray *bdt = new QByteArray(data, 12);
    return {2,bdt};
}

int configs::load_eth_configs(tcpIntrfc *cl) { // send message to load params from device
    tcpC->setReadyRead_loadDev(cl);
    ret_t rez = load_eth_configs_bArray();
    if(rez.res < 0) return -1;
    else if(tcpC->sendToTcp(rez.bdata) > 0) {
        qDebug("success /n");
        // тут разбор и запись в configs -> parms
        return 0;
    }
    else return -2;
}

int configs::load_eth_configs_resp(){ // respond after load params from device and parsing
    QByteArray ba = tcpC->getAll();
    if(ba == nullptr) return -2;
    else  if (ba[0] != 'Q' || ba[0x3D] != 'G' || ba[0x3E] != 'B') return -1;
    else {
        if ((ba[1] & 0x01) != 0) { cnfg.otnositelnoe_otobragenie = true; } else { cnfg.otnositelnoe_otobragenie = false; }
        if ((ba[1] & 0x02) != 0) { cnfg.inversion_data = true; } else { cnfg.inversion_data = false; }
                        //if ((data[1] & 0x04) != 0) { GL.otkl_panel = true; } else { GL.otkl_panel = false; }
                        //if ((data[1] & 0x08) != 0) { GL.sensorReset = true; } else { GL.sensorReset = false; }
        if ((ba[1] & 0x10) != 0) { cnfg.avariya[0].avariya1_predupregdenie0 = 1; } else { cnfg.avariya[0].avariya1_predupregdenie0 = 0; }
        if ((ba[1] & 0x20) != 0) { cnfg.avariya[1].avariya1_predupregdenie0 = 1; } else { cnfg.avariya[1].avariya1_predupregdenie0 = 0; }
        if ((ba[1] & 0x40) != 0) { cnfg.avariya[2].avariya1_predupregdenie0 = 1; } else { cnfg.avariya[2].avariya1_predupregdenie0 = 0; }
        if ((ba[1] & 0x80) != 0) { cnfg.avariya[3].avariya1_predupregdenie0 = 1; } else { cnfg.avariya[3].avariya1_predupregdenie0 = 0; }
        int timeout_alarm;
        timeout_alarm = ba[2]; timeout_alarm <<= 8; timeout_alarm |= ba[3];
        cnfg.timeout_alarm = (double)timeout_alarm;
        int ipi[4], maska[4], t_ip2[4], t_ip3[4];

        for (int i = 0; i < 4; i++)
        {
            int j = i + 4; ipi[i] = ba[j];
            j = i + 8; maska[i] = ba[j];
            j = i + 12; t_ip2[i] = ba[j];
            j = i + 16; t_ip3[i] = ba[j];
        }
        cnfg.ethIP_extr = QString::number(t_ip2[0]) + "." + QString::number(t_ip2[1]) + "." + QString::number(t_ip2[2]) + "." + QString::number(t_ip2[3]);
        cnfg.ethPORT_extr = (t_ip3[0] << 8) | (t_ip3[1]); cnfg.ethPORT = (t_ip3[2] << 8) | (t_ip3[3]);
        cnfg.ethMASK = QString::number(maska[0]) + "." + QString::number(maska[1]) + "." + QString::number(maska[2]) + "." + QString::number(maska[3]);
        cnfg.ethIP = QString::number(ipi[0]) + "." + QString::number(ipi[1]) + "." + QString::number(ipi[2]) + "." + QString::number(ipi[3]);
        for (int i = 0; i < 8; i++)
        {
            int j = i * 2; j = j + 20;
            uint16_t smehenie = ba[j]; j++;
            smehenie = (uint16_t)(smehenie << 8);
            smehenie = (uint16_t)(smehenie | ba[j]);
            int16_t re = (int16_t)smehenie;
            cnfg.data[i].smeshenie = re;
            cnfg.data[i].smeshenie = cnfg.data[i].smeshenie / 2.0;
        }
        cnfg.avariya[0].kolvo_avariynih_datchikov = (ba[40] >> 4) & 0x0F;
        cnfg.avariya[1].kolvo_avariynih_datchikov = ba[40] & 0x0F;
        cnfg.avariya[2].kolvo_avariynih_datchikov = (ba[41] >> 4) & 0x0F;
        cnfg.avariya[3].kolvo_avariynih_datchikov = ba[41] & 0x0F;
        int sm = 42;
        for (int i = 0; i < 4; i++)
        {
            int16_t porog = ba[sm]; sm++;
            porog = (int16_t)((porog << 8) | ba[sm]); sm++;
            cnfg.avariya[i].porog_max = porog;
            porog = ba[sm]; sm++;
            porog = (int16_t)((porog << 8) | ba[sm]); sm++;
            cnfg.avariya[i].porog_min = porog;
        }
        cnfg.porog_max = ba[36]; cnfg.porog_max = (int16_t)((cnfg.porog_max << 8) + ba[37]);
        cnfg.porog_min = ba[38]; cnfg.porog_min = (int16_t)((cnfg.porog_min << 8) + ba[39]);
        cnfg.version_proshivki = ba[58]; cnfg.version_proshivki = (int16_t)(cnfg.version_proshivki << 8);
        cnfg.version_proshivki = (int16_t)(cnfg.version_proshivki | ba[59]);
//        MessageBox.Show("Новые параметры получены");

        cnfg.obnovlenie_proshivki = true;
    }
    // здесь получили, разбор сообщения, запись в cnfg
    return 0;
}

//int configs::save_view_configs() {
//    return 0;
//}

//int configs::load_view_configs() {
//    return 0;
//}

QList<QString>* configs::fillList() {
    QList<QString> *ls = new QList<QString>();
    ls->append(cnfg.ethIP);
    ls->append(cnfg.ethIP_new);
    ls->append(cnfg.ethMASK);
    ls->append(cnfg.ethMASK_new);
    ls->append(cnfg.ethPORT);
    ls->append(cnfg.ethPORT_new);
    return ls;
}

int configs::fillCfg(QList<QString> &ls) {
    cnfg.ethIP = ls[0];
    cnfg.ethIP_new = ls[1];
    cnfg.ethMASK = ls[2];
    cnfg.ethMASK_new = ls[3];
    cnfg.ethPORT = ls[4];
    cnfg.ethPORT_new = ls[5];
    return 0;
}

int configs::setReadyRead_loadDev(tcpIntrfc *cl) {
    tcpC->setReadyRead_loadDev(cl);
    ret_t res = save_eth_configs_bArray();
    tcpC->sendToTcp(res.bdata);
//    else if(str == "") tcpC->setReadyReadSlot(cl->loadChart_readyRead);
    return 0;
}

//int configs::setReadyRead_saveDev(tcpIntrfc *cl) {
//    tcpC->setReadyRead_saveDev(cl);
//    return 0;
//}

//int configs::setReadyRead_loadChart(tcpIntrfc *cl) {
//    tcpC->set_loadChart_ReadyReadSlot(cl);
//    return 0;
//}

