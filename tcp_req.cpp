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

glob::glob(QObject *parent = nullptr) {
    otnositelnoe_otobragenie = 0;
    inversion_data = true;
    inversion_dt = false;
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
    timeout_alarm = 2;
    version_proshivki = 0;
    alarmt = 4;
    IP = "192.168.1.170";
    IP_new = "192.168.1.170";
    MASK = "255.255.0.0";
    MASKA = "255.255.0.0";
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

        mashtab = 10;
        graph_memory = 100;
        obnovlenie_proshivki = false;
        config_file = "config.ini";
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
    glob* gl = new glob();
//    glob& GL = *gl1;
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
        if (gl->otnositelnoe_otobragenie == true) { tbdata = 1; } else { tbdata = 0; }
        if (gl->inversion_data == true) { tbdata += 0x02; }
        //if (GL.otkl_panel == true) { bdata[1 + pr] += 0x04; }
        //if (GL.sensorReset == true) { bdata[1 + pr] += 0x08; }
        if (gl->avariya[0].avariya1_predupregdenie0 == 1) { tbdata += 0x10; }//avariya1_predupregdenie0 == 1, когда выбран тип "Авария"
        if (gl->avariya[1].avariya1_predupregdenie0 == 1) { tbdata += 0x20; }
        if (gl->avariya[2].avariya1_predupregdenie0 == 1) { tbdata += 0x40; }
        if (gl->avariya[3].avariya1_predupregdenie0 == 1) { tbdata += 0x80; }
        bdata[1 + pr] = tbdata;
        uint16_t time = gl->timeout_alarm;
        bdata[3 + pr] = static_cast<uchar>(time); //time = Convert.ToUInt16(time >> 8);
        bdata[2 + pr] = static_cast<uchar>(time>>8);

        uint8_t ip[4];
        if (!gl->check_IP(ip)) { return {1, bdt}; }
        for (i = 0; i < n_avar; i++) { bdata[i + 4 + pr] = ip[i]; }
        // maska
        //flag = string_to_ip(text_maska_new.Text, ref ip, 2);
        if (!gl->check_MASK(ip)) { return {1, bdt}; }
        for (i = 0; i < n_avar; i++) { bdata[i + 8 + pr] = ip[i]; }

        //int sp = Convert.ToInt32(text_sport_new.Text);
        uint16_t dp = gl->DPORT_new.toShort();
        //bdata[17 + pr] = (byte)(sp & 0x00FF);
        //bdata[16 + pr] = (byte)((sp >> 8) & 0x00FF);
        bdata[19 + pr] = static_cast<uint8_t>(dp & 0x00FF);
        bdata[18 + pr] = static_cast<uint8_t>((dp >> 8) & 0x00FF);

        int smechenie = 20;
        for (i = 0; i < n_dat; i++)
        {
            double dd = gl->data[i].smeshenie * 2.0;
            int idd = static_cast<uint16_t>(dd);
            bdata[smechenie + pr] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
            bdata[smechenie + pr] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
        }
        int ipr = gl->porog_max;
        bdata[37 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdata[36 + pr] = static_cast<uint8_t>(ipr & 0x00FF);

        ipr = gl->porog_min;
        bdata[39 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdata[38 + pr] = static_cast<uint8_t>(ipr & 0x00FF);


        bdata[40 + pr] = static_cast<uint8_t>((((gl->avariya[0].kolvo_avariynih_datchikov << 4) & 0xF0) | (gl->avariya[1].kolvo_avariynih_datchikov & 0x0F)));
        bdata[41 + pr] = static_cast<uint8_t>((((gl->avariya[2].kolvo_avariynih_datchikov << 4) & 0xF0) | (gl->avariya[3].kolvo_avariynih_datchikov & 0x0F)));

        smechenie = 42;
        for (i = 0; i < n_avar; i++)
        {
            int idd = gl->avariya[i].porog_max;
            bdata[smechenie + pr] = static_cast<uint8_t>((idd >> 8) & 0x00FF); smechenie++;
            bdata[smechenie + pr] = static_cast<uint8_t>(idd & 0x00FF); smechenie++;
            idd = gl->avariya[i].porog_min;
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
        gl->version_proshivki = Crc16(crc, 58 + pr);
        ipr = gl->version_proshivki;
        bdata[59 + pr] = static_cast<uint8_t>(ipr & 0x00FF); ipr = ipr >> 8;
        bdata[58 + pr] = static_cast<uint8_t>(ipr & 0x00FF);

        // ////////////////////////////////////////
        ipr = gl->alarmt;
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

#include <QFile>
#include <QTextStream>

int glob::save_configs() {
/*
 *  Messagebox open file if we need something unusual.
 *
    QString sf = GL.config_file;

    saveFileDialog_ini.FileName = "";
    if (MessageBox.Show("Сохранить настройки ПТК КМ-Дельта в отдельный файл?", "", MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
    {
        if (saveFileDialog_ini.ShowDialog() == DialogResult.OK)
            if (saveFileDialog_ini.FileName != GL.save_file)
            {
                sf = saveFileDialog_ini.FileName;                   //System.IO.File.Copy(GL.save_file, saveFileDialog1.FileName, true);
            }
    }
    else { MessageBox.Show("Параметры будут сохранены в файл по умолчанию"); }
*/
    QFile cfile(config_file);
    if (!cfile.open(QIODevice::WriteOnly | QIODevice::Text))
            return -1;
    QTextStream wr(&cfile);
//    using (StreamWriter wr = new StreamWriter(sf, false))
    {
        wr << "IP-адрес ПТК КМ-Дельта:" + IP << "\n";
        wr << "Маска подсети:" + MASKA << "\n";
        wr << "Удалённый IP1:" + IP1 << "\n";
        wr << "Порт ПТК КМ-Дельта:" + DPORT << "\n";
        //wr << "Порт программы:" + SPORT << "\n";
        wr << "Задержка срабатывания сигнализации:" + QString::number(timeout_alarm) << "\n";
        wr << "Масштаб отображения, с:" + QString::number(mashtab) << "\n";
        wr << "Отображение относительных данных:" + QString::number(otnositelnoe_otobragenie) << "\n";
        wr << "Смещение канала 1, мкм:" + QString::number(data[0].smeshenie) << "\n";
        wr << "Смещение канала 2, мкм:" + QString::number(data[1].smeshenie) << "\n";
        wr << "Смещение канала 3, мкм:" + QString::number(data[2].smeshenie) << "\n";
        wr << "Смещение канала 4, мкм:" + QString::number(data[3].smeshenie) << "\n";
        wr << "Смещение канала 5, мкм:" + QString::number(data[4].smeshenie) << "\n";
        wr << "Смещение канала 6, мкм:" + QString::number(data[5].smeshenie) << "\n";
        wr << "Смещение канала 7, мкм:" + QString::number(data[6].smeshenie) << "\n";
        wr << "Смещение канала 8, мкм:" + QString::number(data[7].smeshenie) << "\n";
        for (int i = 0; i < 4; i++)
        {
            QString str = "Реле " + QString::number(i + 1) + " верхний порог: "; wr << str + QString::number(avariya[i].porog_max) << "\n";
            str = "Реле " + QString::number(i + 1) + " нижний порог: "; wr << str + QString::number(avariya[i].porog_min) << "\n";
            str = "Реле " + QString::number(i + 1) + " аварийные датчики: "; wr << str + QString::number(avariya[i].kolvo_avariynih_datchikov) << "\n";
            str = "Реле " + QString::number(i + 1) + " признак сигнализации: "; wr << str + QString::number(avariya[i].avariya1_predupregdenie0) << "\n";
        }
        wr << "Максимум шкалы:" + QString::number(porog_max) << "\n";
        wr << "Минимум шкалы:" + QString::number(porog_min) << "\n";
        wr << "Инверсия данных:" + QString::number(inversion_data) << "\n";
        //wr.WriteLine("Отключение реле:" + GL.otkl_panel.ToString());
        //wr.WriteLine("Сброс датчиков:" + GL.sensorReset.ToString());
        wr << "Память, точек:" + QString::number(graph_memory) << "\n";
        wr << "Версия прошивки:" + QString::number(version_proshivki) << "\n";
        wr << "Time_sec:" + QString::number(alarmt) << "\n";
//        wr.Close();
        cfile.close();
    }
}
int glob::load_configs() {
    //DialogResult dr = MessageBox.Show("Загрузить настройки ПТК КМ-Дельта из отдельного файла?", "", MessageBoxButtons.YesNo);
    /*            if (FormMessBox.dr == DialogResult.Yes)
                        {
                            if (openFileDialog1.ShowDialog() != DialogResult.OK) { GL.open_file = GL.config_file; }// return;
                            else { GL.open_file = openFileDialog1.FileName; }
                        }
                        else { GL.open_file = GL.config_file; }
            */
    /*
    GL.open_file = FormMessBox.open_file;
    if (File.Exists(GL.open_file) != true) { return -1; }
    */
    QFile cfile(config_file);
    if (!cfile.open(QIODevice::ReadOnly | QIODevice::Text))
            return -1;
    QTextStream rd(&cfile);

//    using (StreamReader rd = new StreamReader(GL.open_file))//System.IO.StreamReader rd= new System.IO.StreamReader(GL.config_file);
    {
//        try
        {
            QString str = rd.readLine(); int ind = str.indexOf(':'); ind++; IP = str.mid(ind, str.length() - ind);
            str = rd.readLine(); ind = str.indexOf(':'); ind++; MASKA = str.mid(ind, str.length() - ind);
            str = rd.readLine(); ind = str.indexOf(':'); ind++; IP1 = str.mid(ind, str.length() - ind);
            str = rd.readLine(); ind = str.indexOf(':'); ind++; DPORT = str.mid(ind, str.length() - ind);
            //str = rd.readLine(); ind = str.indexOf(':'); ind++; SPORT = (str.mid(ind, str.length() - ind)).toInt();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; timeout_alarm = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; mashtab = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; otnositelnoe_otobragenie = (str.mid(ind, str.length() - ind) == QString("true"));
            str = rd.readLine(); ind = str.indexOf(':'); ind++; data[0].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; data[1].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; data[2].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; data[3].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; data[4].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; data[5].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; data[6].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; data[7].smeshenie = (str.mid(ind, str.length() - ind)).toDouble();
            for (int i = 0; i < 4; i++)
            {
                str = rd.readLine(); ind = str.indexOf(':'); ind++; avariya[i].porog_max = (str.mid(ind, str.length() - ind)).toInt();
                str = rd.readLine(); ind = str.indexOf(':'); ind++; avariya[i].porog_min = (str.mid(ind, str.length() - ind)).toInt();
                str = rd.readLine(); ind = str.indexOf(':'); ind++; avariya[i].kolvo_avariynih_datchikov = (str.mid(ind, str.length() - ind)).toInt();
                str = rd.readLine(); ind = str.indexOf(':'); ind++; avariya[i].avariya1_predupregdenie0 = (str.mid(ind, str.length() - ind)).toInt();
            }
            str = rd.readLine(); ind = str.indexOf(':'); ind++; porog_max = (str.mid(ind, str.length() - ind)).toShort();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; porog_min = (str.mid(ind, str.length() - ind)).toShort();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; inversion_data = (str.mid(ind, str.length() - ind)== QString("true"));
            //str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; gl.otkl_panel = Convert.ToBoolean(str.Substring(ind, str.Length - ind));
            //sensorReset = true;                     str = rd.ReadLine();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; graph_memory = (str.mid(ind, str.length() - ind)).toInt();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; version_proshivki = (str.mid(ind, str.length() - ind)).toUShort();
            str = rd.readLine(); ind = str.indexOf(':'); ind++; alarmt = (str.mid(ind, str.length() - ind)).toShort();
            cfile.close();
        }
//        catch
        {
            cfile.close();
//            MessageBox.Show("Ошибка чтения файла! Перезапустите программу.");
            emit mesBox("Ошибка чтения файла! Перезапустите программу.");
//            System.IO.File.Delete(gl.config_file);
//            this.Dispose();
        }
    }
    //MessageBox.Show("*****Settings has been Loaded*****");
    return 0;
}

