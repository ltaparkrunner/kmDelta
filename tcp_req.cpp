#include "tcp_req.h"
#include "crc32.h"
#include <QByteArray>
#include <QHostAddress>

Data::Data(){
   absolutnoe = 0.0;
   smeshenie = 0.0;
}

avar::avar() {
    avariya1_predupregdenie0 = 0;
    porog_max = 0;
    porog_min = 0;
    kolvo_avariynih_datchikov = 0;
}

glob::glob() {
    otnositelnoe_otobragenie = 0;
    inversion_data = true;

    avariya[0].avariya1_predupregdenie0 = 1;
    avariya[0].kolvo_avariynih_datchikov = 1;
    avariya[0].porog_max = 420;
    avariya[0].porog_min = 560;
    avariya[1].avariya1_predupregdenie0 = 0;
    avariya[1].kolvo_avariynih_datchikov = 1;
    avariya[1].porog_max = 380;
    avariya[1].porog_min = 720;

    for(int i = 2; i < n_avar; i++)
    {
        avariya[i].avariya1_predupregdenie0 = 0;
        avariya[i].kolvo_avariynih_datchikov = 0;
        avariya[i].porog_max = 0;
        avariya[i].porog_min = 0;
    }
    porog_max = 420;
    porog_min = 560;
    version_proshivki = 0;
    alarmt = 4;
    IP = "192.168.1.170";
    IP_new = "192.168.1.170";
    MASK = "255.255.0.0";
    DPORT = "502";
    DPORT_new = "503";

//    for(int i = 0; i < n_dat; i++)
//    {
//        data[i].absolutnoe = 0;
//        data[i].smeshenie = 0;
//    }
        data[0].absolutnoe = 0;
        data[0].smeshenie = -273.5;
        data[1].absolutnoe = 0;
        data[1].smeshenie = -2648.5;
        data[2].absolutnoe = 0;
        data[2].smeshenie = -711.5;
        data[3].absolutnoe = 0;
        data[3].smeshenie = -1910.5;
        data[4].absolutnoe = 0;
        data[4].smeshenie = -845.5;
        data[5].absolutnoe = 0;
        data[5].smeshenie = -1519.5;
        data[6].absolutnoe = 0;
        data[6].smeshenie = -1736.0;
        data[7].absolutnoe = 0;
        data[7].smeshenie = -1612.0;
}

bool glob::check_IP(uint8_t ip[]){
    if (IP.count('.') < 3) return false;
    auto i = IP.split('.').begin();
    for(int i1 = 0; i1 < 4; i1++){
        uint8_t t1 = (*i).toShort();
        ip[i1] = t1;
    }
    return true;
}
/*
temporary-iterator

            Detects when you're using using functions returning iterators (eg. begin() or end()) on a temporary container.
Example

                    // temporary list returned by function
                    QList<type> getList()
{
    QList<type> list;
    ... add some items to list ...
        return list;
}

// Will cause a crash if iterated using:

for (QList<type>::iterator it = getList().begin(); it != getList().end(); ++it)
{
    ...
}

because the end iterator was returned from a different container object than the begin iterator.
*/

bool glob::check_MASK(uint8_t ip[]){
    if (IP.count('.') < 3) return false;
    auto i = IP.split('.').begin();
    for(int i1 = 0; i1 < 4; i1++){
        uint8_t t1 = (*i).toShort();
        ip[i1] = t1;
    }
    return true;
}


//uint32_t crc32(QByteArray m){
//    uint8_t crc[m.length];
//    for (int i = 0; i < 58 + pr; i++)
//    {
//        crc[i] = bdata[i];
//    }

//}

//ret_t tcp_req::tcp_req_init()
ret_t tcp_req::period_req() {
//    QByteArray *bdt = new QByteArray();
//    return {2,bdt};
    const char data[12] = {1, 1, 0,0,0,6,33,3,0,0,0,16};
    QByteArray *bdt = new QByteArray(data, 12);
    return {2,bdt};
}

ret_t tcp_req::set_params()
{
    const int pr = 10;
    glob GL = glob();
    QByteArray *bdt = new QByteArray();
//    try
    {

        QByteArray &bdata = *bdt;
// = new QByteArray(72, 0);
//        QByteArray ip = QByteArray(4, 0);
//        int flag;
        int i;
        bdata[0] = 'G';//Идификатор транзакции
        bdata[1] = 'B';//Идификатор транзакции
        bdata[2] = 0;//Идификатор протокола
        bdata[3] = 0;//Идификатор протокола
        bdata[4] = 0;//Длина
        bdata[5] = 0x3E;//Длина
        bdata[6] = 'A';//Адрес
        bdata[7] = 0x10;//Функциональный код
        bdata[8] = 0;//Адрес первого регистра
        bdata[9] = 0x33;//Адрес первого регистра
        bdata[10] = 0;

        char tbdata = 0;
        if (GL.otnositelnoe_otobragenie == true) { tbdata = 1; } else { tbdata = 0; }
        if (GL.inversion_data == true) { tbdata += 0x02; }
        //if (GL.otkl_panel == true) { bdata[1 + pr] += 0x04; }
        //if (GL.sensorReset == true) { bdata[1 + pr] += 0x08; }
        if (GL.avariya[0].avariya1_predupregdenie0 == 1) { tbdata += 0x10; }//avariya1_predupregdenie0 == 1, когда выбран тип "Авария"
        if (GL.avariya[1].avariya1_predupregdenie0 == 1) { tbdata += 0x20; }
        if (GL.avariya[2].avariya1_predupregdenie0 == 1) { tbdata += 0x40; }
        if (GL.avariya[3].avariya1_predupregdenie0 == 1) { tbdata += 0x80; }
        bdata[1 + pr] = tbdata;
        uint16_t time = GL.timeout_alarm;
        bdata[3 + pr] = static_cast<uchar>(time); //time = Convert.ToUInt16(time >> 8);
        bdata[2 + pr] = static_cast<uchar>(time>>8);

        uint8_t ip[4];
        if (!GL.check_IP(ip)) { return {1, bdt}; }
        for (i = 0; i < n_avar; i++) { bdata[i + 4 + pr] = ip[i]; }
        // maska
        //flag = string_to_ip(text_maska_new.Text, ref ip, 2);
        if (!GL.check_MASK(ip)) { return {1, bdt}; }
        for (i = 0; i < n_avar; i++) { bdata[i + 8 + pr] = ip[i]; }

        //int sp = Convert.ToInt32(text_sport_new.Text);
        uint16_t dp = GL.DPORT_new.toShort();
        //bdata[17 + pr] = (byte)(sp & 0x00FF);
        //bdata[16 + pr] = (byte)((sp >> 8) & 0x00FF);
        bdata[19 + pr] = static_cast<uint8_t>(dp & 0x00FF);
        bdata[18 + pr] = static_cast<uint8_t>((dp >> 8) & 0x00FF);

        int smechenie = 20;
        for (i = 0; i < n_dat; i++)
        {
            double dd = GL.data[i].smeshenie * 2.0;
            int idd = static_cast<uint16_t>(dd);
            bdata[smechenie + pr] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
            bdata[smechenie + pr] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
        }
        int ipr = GL.porog_max;
        bdata[37 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdata[36 + pr] = static_cast<uint8_t>(ipr & 0x00FF);

        ipr = GL.porog_min;
        bdata[39 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdata[38 + pr] = static_cast<uint8_t>(ipr & 0x00FF);


        bdata[40 + pr] = static_cast<uint8_t>((((GL.avariya[0].kolvo_avariynih_datchikov << 4) & 0xF0) | (GL.avariya[1].kolvo_avariynih_datchikov & 0x0F)));
        bdata[41 + pr] = static_cast<uint8_t>((((GL.avariya[2].kolvo_avariynih_datchikov << 4) & 0xF0) | (GL.avariya[3].kolvo_avariynih_datchikov & 0x0F)));

        smechenie = 42;
        for (i = 0; i < n_avar; i++)
        {
            int idd = GL.avariya[i].porog_max;
            bdata[smechenie + pr] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
            bdata[smechenie + pr] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
            idd = GL.avariya[i].porog_min;
            bdata[smechenie + pr] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
            bdata[smechenie + pr] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
        }
/*
        byte[] crc = new byte[58 + pr];
        for (i = 0; i < 58 + pr; i++)
        {
            crc[i] = bdata[i];
        }
        crc32 crc_f = new crc32();
        GL.version_proshivki = crc_f.Crc16(crc, 58 + pr);
*/

        QByteArray crc = bdata; //[] = new byte[58 + pr];

        uint32_t crc_f = crc32(crc, crc.length());
//        crc32(crc, crc.length());
        GL.version_proshivki = Crc16(crc, 58 + pr);
        ipr = GL.version_proshivki;
        bdata[59 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdata[58 + pr] = static_cast<uint8_t>(ipr & 0x00FF);

        // ////////////////////////////////////////
        ipr = GL.alarmt;
        bdata[60 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdata[61 + pr] = static_cast<uint8_t>(ipr & 0x00FF);

        // ////////////////////////////////////////

        //текущий IP и порт
/*
        GL.IP = text_ip_old.Text;
        GL.DPORT = Convert.ToUInt16(text_dport_old.Text);
        TCP = null;Thread.Sleep(500);
        TCP = new tcp.tcp_client();
        if (TCP.tcp_start(GL.IP, GL.DPORT) < 0) { return 2; }
        TCP.tcp_send(bdata, 72, text_ip_old.Text, GL.DPORT);
            byte[] rez = TCP.recive(); TCP.tcp_stop();
            if (rez == null) { return 2; }
            if (rez[1] == Convert.ToByte('O') && rez[2] == Convert.ToByte('K') && rez[3] == Convert.ToByte('!'))
            {
                MessageBox.Show("Параметры успешно установлены!");return 0;
            }
*/
        return {2, bdt};
    }
/*
    catch (FormatException ee) { return 1; }
    catch (Exception ee) { return 2; }
    finally
    {
        TCP.tcp_stop(); TCP = null;
    }
*/
    return {0, bdt};
}

ret_t tcp_req::req_param() {
//    QByteArray *bdt = new QByteArray(12, {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0});
    const char data[12] = {0x47, 0x42, 0,0,0,6,0x41,3,0,0x33,0,0};
    QByteArray *bdt = new QByteArray(data, 12);
    return {2,bdt};
}
