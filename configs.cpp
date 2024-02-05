#include "configs.h"

int configs::save_configs() {

    if (G3 != null) GL = G3;
    string sf = GL.config_file; saveFileDialog_ini.FileName = "";
    if (MessageBox.Show("Сохранить настройки ПТК КМ-Дельта в отдельный файл?", "", MessageBoxButtons.YesNo) == System.Windows.Forms.DialogResult.Yes)
    {
        if (saveFileDialog_ini.ShowDialog() == DialogResult.OK)
            if (saveFileDialog_ini.FileName != GL.save_file)
            {
                sf = saveFileDialog_ini.FileName;                   //System.IO.File.Copy(GL.save_file, saveFileDialog1.FileName, true);
            }
    }
    //else { MessageBox.Show("Параметры будут сохранены в файл по умолчанию"); }
    using (StreamWriter wr = new StreamWriter(sf, false))
    {
        wr.WriteLine("IP-адрес ПТК КМ-Дельта:" + GL.IP);
        wr.WriteLine("Маска подсети:" + GL.MASKA);
        wr.WriteLine("Удалённый IP1:" + GL.IP1);
        wr.WriteLine("Порт ПТК КМ-Дельта:" + GL.DPORT.ToString());
        wr.WriteLine("Порт программы:" + GL.SPORT.ToString());
        wr.WriteLine("Задержка срабатывания сигнализации:" + GL.timeout_alarm.ToString());
        wr.WriteLine("Масштаб отображения, с:" + GL.mashtab.ToString());
        wr.WriteLine("Отображение относительных данных:" + GL.otnositelnoe_otobragenie.ToString());
        wr.WriteLine("Смещение канала 1, мкм:" + GL.data[0].smeshenie.ToString());
        wr.WriteLine("Смещение канала 2, мкм:" + GL.data[1].smeshenie.ToString());
        wr.WriteLine("Смещение канала 3, мкм:" + GL.data[2].smeshenie.ToString());
        wr.WriteLine("Смещение канала 4, мкм:" + GL.data[3].smeshenie.ToString());
        wr.WriteLine("Смещение канала 5, мкм:" + GL.data[4].smeshenie.ToString());
        wr.WriteLine("Смещение канала 6, мкм:" + GL.data[5].smeshenie.ToString());
        wr.WriteLine("Смещение канала 7, мкм:" + GL.data[6].smeshenie.ToString());
        wr.WriteLine("Смещение канала 8, мкм:" + GL.data[7].smeshenie.ToString());
        for (int i = 0; i < 4; i++)
        {
            string str = "Реле " + (i + 1).ToString() + " верхний порог:"; wr.WriteLine(str + GL.avariya[i].porog_max.ToString());
            str = "Реле " + (i + 1).ToString() + " нижний порог:"; wr.WriteLine(str + GL.avariya[i].porog_min.ToString());
            str = "Реле " + (i + 1).ToString() + " аварийные датчики:"; wr.WriteLine(str + GL.avariya[i].kolvo_avariynih_datchikov.ToString());
            str = "Реле " + (i + 1).ToString() + " признак сигнализации:"; wr.WriteLine(str + GL.avariya[i].avariya1_predupregdenie0.ToString());
        }
        wr.WriteLine("Максимум шкалы:" + GL.porog_max.ToString());
        wr.WriteLine("Минимум шкалы:" + GL.porog_min.ToString());
        wr.WriteLine("Инверсия данных:" + GL.inversion_data.ToString());
        //wr.WriteLine("Отключение реле:" + GL.otkl_panel.ToString());
        //wr.WriteLine("Сброс датчиков:" + GL.sensorReset.ToString());
        wr.WriteLine("Память, точек:" + GL.graph_memory.ToString());
        wr.WriteLine("Версия прошивки:" + GL.version_proshivki.ToString());
        wr.WriteLine("Time_sec:" + GL.alarmt.ToString());
        wr.Close();
    }
}
int configs::load_configs() {
    //DialogResult dr = MessageBox.Show("Загрузить настройки ПТК КМ-Дельта из отдельного файла?", "", MessageBoxButtons.YesNo);
    /*            if (FormMessBox.dr == DialogResult.Yes)
                        {
                            if (openFileDialog1.ShowDialog() != DialogResult.OK) { GL.open_file = GL.config_file; }// return;
                            else { GL.open_file = openFileDialog1.FileName; }
                        }
                        else { GL.open_file = GL.config_file; }
            */
    GL.open_file = FormMessBox.open_file;
    if (File.Exists(GL.open_file) != true) { return -1; }
    using (StreamReader rd = new StreamReader(GL.open_file))//System.IO.StreamReader rd= new System.IO.StreamReader(GL.config_file);
    {
        try
        {
            string str = rd.ReadLine(); int ind = str.IndexOf(':'); ind++; GL.IP = str.Substring(ind, str.Length - ind);
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.MASKA = str.Substring(ind, str.Length - ind);
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.IP1 = str.Substring(ind, str.Length - ind);
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.DPORT = Convert.ToInt32(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.SPORT = Convert.ToInt32(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.timeout_alarm = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.mashtab = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.otnositelnoe_otobragenie = Convert.ToBoolean(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.data[0].smeshenie = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.data[1].smeshenie = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.data[2].smeshenie = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.data[3].smeshenie = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.data[4].smeshenie = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.data[5].smeshenie = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.data[6].smeshenie = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.data[7].smeshenie = Convert.ToDouble(str.Substring(ind, str.Length - ind));
            for (int i = 0; i < 4; i++)
            {
                str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.avariya[i].porog_max = Convert.ToInt32(str.Substring(ind, str.Length - ind));
                str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.avariya[i].porog_min = Convert.ToInt32(str.Substring(ind, str.Length - ind));
                str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.avariya[i].kolvo_avariynih_datchikov = Convert.ToInt32(str.Substring(ind, str.Length - ind));
                str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.avariya[i].avariya1_predupregdenie0 = Convert.ToInt32(str.Substring(ind, str.Length - ind));
            }
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.porog_max = Convert.ToInt16(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.porog_min = Convert.ToInt16(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.inversion_data = Convert.ToBoolean(str.Substring(ind, str.Length - ind));
            //str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.otkl_panel = Convert.ToBoolean(str.Substring(ind, str.Length - ind));
            //GL.sensorReset = true;                     str = rd.ReadLine();
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.graph_memory = Convert.ToInt32(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.version_proshivki = Convert.ToUInt16(str.Substring(ind, str.Length - ind));
            str = rd.ReadLine(); ind = str.IndexOf(':'); ind++; GL.alarmt = Convert.ToInt16(str.Substring(ind, str.Length - ind));
            rd.Close();
        }
        catch
        {
            rd.Close();
            MessageBox.Show("Ошибка чтения файла! Перезапустите программу.");
            System.IO.File.Delete(GL.config_file);
            this.Dispose();
        }
    }
    //MessageBox.Show("*****Settings has been Loaded*****");
    return 0;
}

