#include "configs.h"
#include "crc32.h"
#include "tcpman.h"
#include <QFile>
#include <QTextStream>

configs::configs(tcp_exch* tcpe):
//    ,cnfg(0)
    te(tcpe)
{
    cnfg.otnositelnoe_otobragenie = 0;
    cnfg.inversion_data = true;
    cnfg.inversion_dt = false;
    cnfg.avariya[0].avariya1_predupregdenie0 = 1;
    cnfg.avariya[0].kolvo_avariynih_datchikov = 1;
    cnfg.avariya[0].porog_max = 420;
    cnfg.avariya[0].porog_min = 560;
    cnfg.avariya[1].avariya1_predupregdenie0 = 0;
    cnfg.avariya[1].kolvo_avariynih_datchikov = 1;
    cnfg.avariya[1].porog_max = 380;
    cnfg.avariya[1].porog_min = 720;

    for(int i = 2; i < n_avar; i++)
    {
        cnfg.avariya[i].avariya1_predupregdenie0 = 0;
        cnfg.avariya[i].kolvo_avariynih_datchikov = 0;
        cnfg.avariya[i].porog_max = 0;
        cnfg.avariya[i].porog_min = 0;
    }
    cnfg.porog_max = 420;
    cnfg.porog_min = 560;
    cnfg.timeout_alarm = 2;
    cnfg.version_proshivki = 0;
    cnfg.alarmt = 4;
    cnfg.IP = "192.168.1.170";
    cnfg.IP1 = "192.168.1.170";
    cnfg.IP_new = "192.168.1.170";
    cnfg.MASK = "255.255.0.0";
    cnfg.MASKA = "255.255.0.0";
    cnfg.DPORT = "502";
    cnfg.DPORT_new = "503";

//    for(int i = 0; i < n_dat; i++)
//    {
//        data[i].absolutnoe = 0;
//        data[i].smeshenie = 0;
//    }
    cnfg.data[0].absolutnoe = 0;
    cnfg.data[0].smeshenie = -273.5;
    cnfg.data[1].absolutnoe = 0;
    cnfg.data[1].smeshenie = -2648.5;
    cnfg.data[2].absolutnoe = 0;
    cnfg.data[2].smeshenie = -711.5;
    cnfg.data[3].absolutnoe = 0;
    cnfg.data[3].smeshenie = -1910.5;
    cnfg.data[4].absolutnoe = 0;
    cnfg.data[4].smeshenie = -845.5;
    cnfg.data[5].absolutnoe = 0;
    cnfg.data[5].smeshenie = -1519.5;
    cnfg.data[6].absolutnoe = 0;
    cnfg.data[6].smeshenie = -1736.0;
    cnfg.data[7].absolutnoe = 0;
    cnfg.data[7].smeshenie = -1612.0;

    cnfg.mashtab = 10;
    cnfg.graph_memory = 100;
    cnfg.obnovlenie_proshivki = false;
//    cnfg.config_file = "config.ini";
}

int configs::save_file_configs(QString filen) {

    QFile cfile(filen);
    if (!cfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return -1;
    QTextStream wr(&cfile);
//    using (StreamWriter wr = new StreamWriter(sf, false))
    {
        wr << "IP-адрес ПТК КМ-Дельта:" + cnfg.IP << "\n";
        wr << "Маска подсети:" + cnfg.MASKA << "\n";
        wr << "Удалённый IP1:" + cnfg.IP1 << "\n";
        wr << "Порт ПТК КМ-Дельта:" + cnfg.DPORT << "\n";
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
}
int configs::load_file_configs(QString filen) {
    QFile cfile(filen);
    if (!cfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return -1;
    QTextStream rd(&cfile);
    {
        QString str = rd.readLine(); int ind = str.indexOf(':'); ind++; cnfg.IP = str.mid(ind, str.length() - ind);
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.MASKA = str.mid(ind, str.length() - ind);
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.IP1 = str.mid(ind, str.length() - ind);
        str = rd.readLine(); ind = str.indexOf(':'); ind++; cnfg.DPORT = str.mid(ind, str.length() - ind);
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
//    if (cnfg.IP.count('.') < 3) return false;
//    auto i = cnfg.IP.split('.').begin();
//    for(int i1 = 0; i1 < 4; i1++){
//        uint8_t t1 = (*i).toShort();
//        ip[i1] = t1;
//    }
//    return true;
//}

ret_t configs::eth_set_params()
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
        if (!check_IP(ip, cnfg.IP)) { return {1, bdata}; }
        for (i = 0; i < n_avar; i++) { bdt[i + 4 + pr] = ip[i]; }
        // maska
        //flag = string_to_ip(text_maska_new.Text, ref ip, 2);
        if (!check_IP(ip, cnfg.MASK)) { return {1, bdata}; }
        for (i = 0; i < n_avar; i++) { bdt[i + 8 + pr] = ip[i]; }

        //int sp = Convert.ToInt32(text_sport_new.Text);
        uint16_t dp = cnfg.DPORT_new.toShort();
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

int configs::save_eth_configs() {

}

ret_t configs::eth_load_params(){
    const char data[12] = {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0};
    QByteArray *bdt = new QByteArray(data, 12);
    return {2,bdt};
}

int configs::load_eth_configs() {

}

int configs::save_view_configs() {

}

int configs::load_view_configs() {

}
