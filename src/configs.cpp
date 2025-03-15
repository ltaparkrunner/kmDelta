#include "configs.h"
#include "crc32.h"
#include "mbtcpClient.h"
#include <QFile>
#include <QTextStream>

parms::parms():
    otnositelnoe_otobragenie( false )
    ,inversion_data(true)
    ,inversion_dt (false)
    ,avariya{{1,1220,620,1},{0,1520,500,1},{0,0,0,0},{0,0,0,0}}
    ,porog_max (420)
    ,porog_min (560)
    ,timeout_alarm (2)
    ,version_proshivki (0)
    ,alarmt (4)
    ,tcpIP ("192.168.1.80")
//    ,IP1 ("192.168.1.170")
    ,tcpIP_new ("192.168.1.170")
    ,tcpMASK ("255.255.0.0")
    ,tcpMASK_new ("255.255.0.0")
    ,tcpPORT ("502")
    ,tcpPORT_new ("503")
 //   ,data ({{0, -273.5}, {0, -2648.5}, {0, -711.5}, {0, -1910.5}, {0, -845.5}, {0, -1519.5}, {0, -1736.0}, {0, -1612.0}})
    ,data {{0, -273}, {0, -2648}, {0, -711}, {0, -1910}, {0, -845}, {0, -1519}, {0, -1736}, {0, -1612}}
    ,mashtab (10)
    ,graph_memory (100)
    ,obnovlenie_proshivki (false)
{ }

int parms::set_default() {
    otnositelnoe_otobragenie = false;
    inversion_data = true;
    inversion_dt = false;
//    avariya = ({{1,420,560,1},{0,380,720,1},{0,0,0,0},{0,0,0,0}});
    //avariya = {1,420,560,1}; //,{0,380,720,1},{0,0,0,0},{0,0,0,0}});
    avariya[0].porog_max = 1220;
    avariya[0].porog_min = 620;
    avariya[0].kolvo_avariynih_datchikov = 1;
    avariya[0].avariya1_predupregdenie0 = 0;

    avariya[1].porog_max = 1520;
    avariya[1].porog_min = 500;
    avariya[1].kolvo_avariynih_datchikov = 1;
    avariya[1].avariya1_predupregdenie0 = 1;

    avariya[2].porog_max = 0;
    avariya[2].porog_min = 0;
    avariya[2].kolvo_avariynih_datchikov = 0;
    avariya[2].avariya1_predupregdenie0 = 0;

    avariya[3].porog_max = 0;
    avariya[3].porog_min = 0;
    avariya[3].kolvo_avariynih_datchikov = 0;
    avariya[3].avariya1_predupregdenie0 = 0;

    porog_max = 420;
    porog_min = 560;
    timeout_alarm = 2;
    version_proshivki = 0;
    alarmt = 4;
    tcpIP = "192.168.1.80";
//    ,IP1 ("192.168.1.170")
    tcpIP_new = "192.168.1.170";
    tcpMASK = "255.255.0.0";
    tcpMASK_new = "255.255.0.0";
    tcpPORT = "502";
    tcpPORT_new = "503";
 //   ,data ({{0, -273.5}, {0, -2648.5}, {0, -711.5}, {0, -1910.5}, {0, -845.5}, {0, -1519.5}, {0, -1736.0}, {0, -1612.0}})
 //   data = ({{0, -273}, {0, -2648}, {0, -711}, {0, -1910}, {0, -845}, {0, -1519}, {0, -1736}, {0, -1612}});
    data[0].absolutnoe = 0;
    data[0].smeshenie = -273;
    data[1].absolutnoe = 0;
    data[1].smeshenie =  -2648;
    data[2].absolutnoe = 0;
    data[2].smeshenie = -711;
    data[3].absolutnoe = 0;
    data[3].smeshenie = -1910;
    data[4].absolutnoe = 0;
    data[4].smeshenie = -845;
    data[5].absolutnoe = 0;
    data[5].smeshenie = -1519;
    data[6].absolutnoe = 0;
    data[6].smeshenie = -1736;
    data[7].absolutnoe = 0;
    data[7].smeshenie = -1612;
    mashtab = 10;
    graph_memory = 100;
    obnovlenie_proshivki = false;
    return 0;
}

configs::configs(/*MbtcpClient* tcpe*/):
//    ,cnfg(0)
//    tcpC(tcpe)
    cnfg(parms())
{ }

configs::configs(QString fn):
    //    ,cnfg(0)
    //    tcpC(tcpe)
    cnfg(parms())
{
/*    if(this -> load_file_configs(fn) != 0)
        ; */  // TODO: send message that couldn't open file
}

int configs::save_file_configs(QString filen) {

    QFile cfile(filen);
    if (!cfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return -1;
    QTextStream wr(&cfile);
//    using (StreamWriter wr = new StreamWriter(sf, false))
    {
        wr << "IP-адрес ПТК КМ-Дельта:" + cnfg.tcpIP << "\n";
        wr << "Маска подсети:" + cnfg.tcpMASK << "\n";
        wr << "Удалённый IP:" + cnfg.tcpIP << "\n";
        wr << "Порт ПТК КМ-Дельта:" + cnfg.tcpPORT << "\n";
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
        QString str = rd.readLine(); int ind = str.indexOf(':'); ind++; cnfg.tcpIP = str.mid(ind, str.length() - ind);
		cnfg.tcpIP_new = cnfg.tcpIP;
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.tcpMASK = str.mid(ind, str.length() - ind);
		cnfg.tcpMASK_new = cnfg.tcpMASK;
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.tcpIP = str.mid(ind, str.length() - ind);
		cnfg.tcpIP_new = cnfg.tcpIP;
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.tcpPORT = str.mid(ind, str.length() - ind);
		cnfg.tcpPORT_new = cnfg.tcpPORT;
//        str = rd.readLine(); ind = str.indexOf(':'); ind++; gl.SPORT = (str.mid(ind, str.length() - ind)).toInt();
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.timeout_alarm = (str.mid(ind, str.length() - ind)).toDouble();   // TODO: Use midRef or doesn't exist??
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
    auto i = ip_s.split('.')/*.begin()*/;   // TODO: Don't call QList::begin() on temporary
    for(int i1 = 0; i1 < 4; i1++){
        uint8_t t1 = i[i1].toShort();
        ip[i1] = t1;
    }
    return true;
}

//bool configs::check_MASK(uint8_t ip[]){
//    if (cnfg.tcpIP.count('.') < 3) return false;
//    auto i = cnfg.tcpIP.split('.').begin();
//    for(int i1 = 0; i1 < 4; i1++){
//        uint8_t t1 = (*i).toShort();
//        ip[i1] = t1;
//    }
//    return true;
//}

int configs::fill_buf(QByteArray &buf, int pos) // save to device
{
    int i = 0;
    char tbdata = 0;
    if (cnfg.otnositelnoe_otobragenie == true) { tbdata = 1; } else { tbdata = 0; }
    if (cnfg.inversion_data == true) { tbdata += 0x02; }
    //if (GL.otkl_panel == true) { bdata[1 + pr] += 0x04; }
    //if (GL.sensorReset == true) { bdata[1 + pr] += 0x08; }
    if (cnfg.avariya[0].avariya1_predupregdenie0 == 1) { tbdata += 0x10; }//avariya1_predupregdenie0 == 1, когда выбран тип "Авария"
    if (cnfg.avariya[1].avariya1_predupregdenie0 == 1) { tbdata += 0x20; }
    if (cnfg.avariya[2].avariya1_predupregdenie0 == 1) { tbdata += 0x40; }
    if (cnfg.avariya[3].avariya1_predupregdenie0 == 1) { tbdata += 0x80; }
    buf[pos] = tbdata;
    uint16_t time = cnfg.timeout_alarm;
    buf[2 + pos] = static_cast<uchar>(time); //time = Convert.ToUInt16(time >> 8);
    buf[1 + pos] = static_cast<uchar>(time>>8);

    uint8_t ip[4];
    if (!check_IP(ip, cnfg.tcpIP_new)) { return 1; }
    for (i = 0; i < n_avar; i++) { buf[i + 3 + pos] = ip[i]; }
    // maska
    //flag = string_to_ip(text_maska_new.Text, ref ip, 2);
    if (!check_IP(ip, cnfg.tcpMASK_new)) { return 1; }
    for (i = 0; i < n_avar; i++) { buf[i + 7 + pos] = ip[i]; }

    //int sp = Convert.ToInt32(text_sport_new.Text);
    uint16_t dp = cnfg.tcpPORT_new.toShort();
    //bdata[17 + pr] = (byte)(sp & 0x00FF);
    //bdata[16 + pr] = (byte)((sp >> 8) & 0x00FF);
    buf[18 + pos] = static_cast<uint8_t>(dp & 0x00FF);
    buf[17 + pos] = static_cast<uint8_t>((dp >> 8) & 0x00FF);

    int smechenie = 20;
    for (i = 0; i < n_dat; i++)
    {
        double dd = cnfg.data[i].smeshenie * 2.0;
        int idd = static_cast<uint16_t>(dd);
        buf[smechenie + pos] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
        buf[smechenie + pos] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
    }
    int ipr = cnfg.porog_max;
    buf[36 + pos] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
    buf[35 + pos] = static_cast<uint8_t>(ipr & 0x00FF);

    ipr = cnfg.porog_min;
    buf[38 + pos] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
    buf[37 + pos] = static_cast<uint8_t>(ipr & 0x00FF);


    buf[39 + pos] = static_cast<uint8_t>((((cnfg.avariya[0].kolvo_avariynih_datchikov << 4) & 0xF0) | (cnfg.avariya[1].kolvo_avariynih_datchikov & 0x0F)));
    buf[40 + pos] = static_cast<uint8_t>((((cnfg.avariya[2].kolvo_avariynih_datchikov << 4) & 0xF0) | (cnfg.avariya[3].kolvo_avariynih_datchikov & 0x0F)));

    smechenie = 41;
    for (i = 0; i < n_avar; i++)
    {
        int idd = cnfg.avariya[i].porog_max;
        buf[smechenie + pos] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
        buf[smechenie + pos] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
        idd = cnfg.avariya[i].porog_min;
        buf[smechenie + pos] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
        buf[smechenie + pos] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
    }
    QByteArray crc = buf; //[] = new byte[58 + pr];

    //uint32_t crc_f =
        crc32(crc, crc.length());
//        crc32(crc, crc.length());
    cnfg.version_proshivki = Crc16(crc, 58 + pos);
    ipr = cnfg.version_proshivki;
    buf[58 + pos] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
    buf[57 + pos] = static_cast<uint8_t>(ipr & 0x00FF);

    // ////////////////////////////////////////
    ipr = cnfg.alarmt;
    buf[59 + pos] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
    buf[60 + pos] = static_cast<uint8_t>(ipr & 0x00FF);

    // ////////////////////////////////////////
    return 0;
}

int configs::save_tcp_configs_resp(MbtcpClient* tcpC) { // respond after save to device
    QByteArray ba = tcpC->getAll();
    if (ba[1] == 'O' && ba[2] == 'K' && ba[3] == '!')  // successfully save to device
        return 0;
    else if (ba == nullptr) return -2;
    else return -1;
}

ret_t configs::load_tcp_configs_bArray(){ // message to respond params from device
    const char data[12] = {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0};
    QByteArray *bdt = new QByteArray(data, 12);
    return {2,bdt};
}

int configs::load_tcp_configs(MbtcpClient* tcpC) { // send message to load params from device
//    tcpC->setReadyRead_loadDev(cl);
    ret_t rez = load_tcp_configs_bArray();
    if(rez.res < 0) return -1;
    else if(tcpC->sendToTcp(rez.bdata) > 0) {
        qDebug("load_tcp_configs   success /n");
        // тут разбор и запись в configs -> parms
        return 0;
    }
    else return -2;
}

int configs::parse_tcp_resp(QByteArray &buf){ // respond after load params from device and parsing

    if(buf == nullptr)
        return -2;
    else  if (buf[0] != 'Q' || buf[0x3D] != 'G' || buf[0x3E] != 'B')
        return -1;
    else {
        if ((buf[1] & 0x01) != 0) { cnfg.otnositelnoe_otobragenie = true; } else { cnfg.otnositelnoe_otobragenie = false; }
        if ((buf[1] & 0x02) != 0) { cnfg.inversion_data = true; } else { cnfg.inversion_data = false; }
                        //if ((data[1] & 0x04) != 0) { GL.otkl_panel = true; } else { GL.otkl_panel = false; }
                        //if ((data[1] & 0x08) != 0) { GL.sensorReset = true; } else { GL.sensorReset = false; }
        if ((buf[1] & 0x10) != 0) { cnfg.avariya[0].avariya1_predupregdenie0 = 1; } else { cnfg.avariya[0].avariya1_predupregdenie0 = 0; }
        if ((buf[1] & 0x20) != 0) { cnfg.avariya[1].avariya1_predupregdenie0 = 1; } else { cnfg.avariya[1].avariya1_predupregdenie0 = 0; }
        if ((buf[1] & 0x40) != 0) { cnfg.avariya[2].avariya1_predupregdenie0 = 1; } else { cnfg.avariya[2].avariya1_predupregdenie0 = 0; }
        if ((buf[1] & 0x80) != 0) { cnfg.avariya[3].avariya1_predupregdenie0 = 1; } else { cnfg.avariya[3].avariya1_predupregdenie0 = 0; }
        int timeout_alarm;
        timeout_alarm = buf[2]; timeout_alarm <<= 8; timeout_alarm |= buf[3];
        cnfg.timeout_alarm = (double)timeout_alarm;
        uint8_t ipi[4], maska[4], t_ip2[4], t_ip3[4];

        for (int i = 0; i < 4; i++)
        {
            int j = i + 4; ipi[i] = buf[j];
            j = i + 8; maska[i] = buf[j];
            j = i + 12; t_ip2[i] = buf[j];
            j = i + 16; t_ip3[i] = buf[j];
        }
        cnfg.tcpIP_extr = QString::number(t_ip2[0]) + "." + QString::number(t_ip2[1]) + "." + QString::number(t_ip2[2]) + "." + QString::number(t_ip2[3]);
        cnfg.tcpPORT_extr = QString::number((t_ip3[0] << 8) | (t_ip3[1])); cnfg.tcpPORT = QString::number((t_ip3[2] << 8) | (t_ip3[3]));
        cnfg.tcpMASK = QString::number(maska[0]) + "." + QString::number(maska[1]) + "." + QString::number(maska[2]) + "." + QString::number(maska[3]);
        cnfg.tcpIP = QString::number(ipi[0]) + "." + QString::number(ipi[1]) + "." + QString::number(ipi[2]) + "." + QString::number(ipi[3]);
        for (int i = 0; i < 8; i++)
        {
            int j = i * 2; j = j + 20;
            uint16_t smehenie = buf[j]; j++;
            smehenie = (uint16_t)(smehenie << 8);
            smehenie = (uint16_t)(smehenie | buf[j]);
            int16_t re = (int16_t)smehenie;
            cnfg.data[i].smeshenie = re;
            cnfg.data[i].smeshenie = cnfg.data[i].smeshenie / 2.0;
        }
        cnfg.avariya[0].kolvo_avariynih_datchikov = (buf[40] >> 4) & 0x0F;
        cnfg.avariya[1].kolvo_avariynih_datchikov = buf[40] & 0x0F;
        cnfg.avariya[2].kolvo_avariynih_datchikov = (buf[41] >> 4) & 0x0F;
        cnfg.avariya[3].kolvo_avariynih_datchikov = buf[41] & 0x0F;
        int sm = 42;
        for (int i = 0; i < 4; i++)
        {
//            int16_t porog = buf[sm]; sm++;
//            porog = (buf[sm] & 0x00ff) | (porog << 8) ; sm++;
            cnfg.avariya[i].porog_max = (buf[sm+1] & 0x00ff) | (buf[sm] << 8);
            sm += 2;
//            porog = buf[sm]; sm++;
//            porog = (buf[sm] & 0x00ff) | (porog << 8); sm++;
            cnfg.avariya[i].porog_min = (buf[sm+1] & 0x00ff) | (buf[sm] << 8);
            sm += 2;
        }
        /*cnfg.porog_max = ; */
        cnfg.porog_max = (int16_t)((buf[36] << 8) + (0x00ff & buf[37]));
        /*cnfg.porog_min = buf[38];*/
        cnfg.porog_min = (int16_t)((buf[38] << 8) + (0x00ff & buf[39]));
        //cnfg.version_proshivki = buf[58];
        //cnfg.version_proshivki = (int16_t)(buf[58] << 8);
        cnfg.version_proshivki = (int16_t)((buf[58] << 8) | (0x00ff & buf[59]));
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
    ls->append(cnfg.tcpIP);
    ls->append(cnfg.tcpIP_new);
    ls->append(cnfg.tcpMASK);
    ls->append(cnfg.tcpMASK_new);
    ls->append(cnfg.tcpPORT);
    ls->append(cnfg.tcpPORT_new);
    return ls;
}

int configs::fillCompareCfg(QList<QString> &ls) {
    int ret = 0;
    if(cnfg.tcpIP != ls[0]){
        cnfg.tcpIP = ls[0];
        ret = 1;
    }
    cnfg.tcpIP_new = ls[1];
    if(cnfg.tcpMASK != ls[2]){
        cnfg.tcpMASK = ls[2];
        ret = 1;
    }
    cnfg.tcpMASK_new = ls[3];
    if(cnfg.tcpPORT != ls[4]){
        cnfg.tcpPORT = ls[4];
        ret = 1;
    }
    cnfg.tcpPORT_new = ls[5];
    return ret;
}

int configs::updateIP(void) {
    cnfg.tcpIP = cnfg.tcpIP_new;
    cnfg.tcpMASK = cnfg.tcpMASK_new;
    cnfg.tcpPORT = cnfg.tcpPORT_new;
    return 0;
}
/*
int configs::setReadyRead_loadDev(MbtcpClient* tcpC, tcpIntrfc *cl) {
//    tcpC->setReadyRead_loadDev(cl);
    ret_t res = save_tcp_configs_bArray();
    tcpC->sendToTcp(res.bdata);
//    else if(str == "") tcpC->setReadyReadSlot(cl->loadChart_readyRead);
    return 0;
}
*/
//int configs::setReadyRead_saveDev(tcpIntrfc *cl) {
//    tcpC->setReadyRead_saveDev(cl);
//    return 0;
//}

//int configs::setReadyRead_loadChart(tcpIntrfc *cl) {
//    tcpC->set_loadChart_ReadyReadSlot(cl);
//    return 0;
//}

int configs::load_tcp_configs_resp(MbtcpClient* tcpC){ // respond after load params from device and parsing
    QByteArray ba = tcpC->getAll();
    if(ba == nullptr)
        return -2;
    else  if (ba[0] != 'Q' || ba[0x3D] != 'G' || ba[0x3E] != 'B')
        return -1;
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
        uint8_t ipi[4], maska[4], t_ip2[4], t_ip3[4];

        for (int i = 0; i < 4; i++)
        {
            int j = i + 4; ipi[i] = ba[j];
            j = i + 8; maska[i] = ba[j];
            j = i + 12; t_ip2[i] = ba[j];
            j = i + 16; t_ip3[i] = ba[j];
        }
        cnfg.tcpIP_extr = QString::number(t_ip2[0]) + "." + QString::number(t_ip2[1]) + "." + QString::number(t_ip2[2]) + "." + QString::number(t_ip2[3]);
        cnfg.tcpPORT_extr = QString::number((t_ip3[0] << 8) | (t_ip3[1])); cnfg.tcpPORT = QString::number((t_ip3[2] << 8) | (t_ip3[3]));
        cnfg.tcpMASK = QString::number(maska[0]) + "." + QString::number(maska[1]) + "." + QString::number(maska[2]) + "." + QString::number(maska[3]);
        cnfg.tcpIP = QString::number(ipi[0]) + "." + QString::number(ipi[1]) + "." + QString::number(ipi[2]) + "." + QString::number(ipi[3]);
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
