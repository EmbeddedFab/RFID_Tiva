using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;
using System.Diagnostics;
using System.Configuration;
using System.Threading;


namespace serialtemplate
{
    public partial class Form1 : Form
    {
        public delegate void InvokeDelegate();

        const byte mode_send            = 2;
        const byte mode_recive          = 1;
        const byte Header               =0xBA;
        const byte Header_rec           =0xBD;
        const byte Select_Card          =0x01;
        const byte Login                =0x02;
        const byte Read_data_block      =0x03;
        const byte Write_data_block     =0x04;
        const byte Read_value_block     =0x05;
        const byte Write_value_block    =0x06;
        const byte Write_master_keyA    =0x07;
        const byte Increment            =0x08;
        const byte Decrement            =0x09;
        const byte Copy                 =0x0A;
        const byte Read_data_page       =0x10;
        const byte Write_data_page      =0x11;
        const byte Control_led          =0x40;
        const byte Reset                =0xFF;

        byte[] serial_buffer = new byte[1000];
        Int32 cnt_seria = 0;
        List<byte> bBuffer = new List<byte>();
        public Form1()
        {
            InitializeComponent();
        }
        private void serialPort_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            recive_box.BeginInvoke(new InvokeDelegate(updateTextbox_));
        
        }

        void updateTextbox_()
        {
            int[] buu = new int[1024];
            int intBytes = serialPort.BytesToRead;
            byte[] bytes = new byte[intBytes];
            serialPort.Read(bytes, 0, intBytes); 
            
            for(int cnt=0;cnt<intBytes;cnt++)
           {
               serial_buffer[cnt_seria] = bytes[cnt];
               cnt_seria++;
           }

            if (serial_buffer[0] == Header_rec)
               {
                   if ((serial_buffer[1] + 2) == (cnt_seria))
                   {
                       byte[] fill_dat = new byte[cnt_seria + 1];
                       for (int i = 0; i < cnt_seria ; i++)
                       {
                           fill_dat[i] = serial_buffer[i];
                       }
                       cnt_seria = 0;
                           show_rec_data(fill_dat);
                   }
               }
    }
      void show_rec_data(byte[] rec_dat)
       {
            recive_box.Text = "";
            
            for (int cnt = 0; cnt < rec_dat.Length-1; cnt++)
            {
                recive_box.Text += Convert.ToString(rec_dat[cnt], 16).PadLeft(2, '0').PadRight(3, ' ').ToUpper();
            }
            status(rec_dat);
          
        }
        void status(byte[] st)
        { 
            switch(st[3])
            {
                case 0:
                    recive_box.Text += "\r\nOperations successfully";
                    if (st[2] == Select_Card)
                    {
                        card_type(st[st[1]]);
                        show_ID_card(st);
                    }
                    if ((st[2] == Read_data_block)|| (st[2] == Read_value_block))
                    {
                        recive_box.Text += ("\r\n Data = ");
                        dataBox.Text = "";

                        for (int cnt = 4; cnt < st[1]+1; cnt++)
                        {
                            if (st[cnt] < 16)
                            {
                                dataBox.Text += "0";
                                recive_box.Text += "0";
                            }
                           
                            dataBox.Text += Convert.ToString(st[cnt], 16).ToUpper();
                            recive_box.Text += Convert.ToString(st[cnt], 16).ToUpper(); 
                            dataBox.Text += " ";
                            recive_box.Text += " "; 
                        }
                    }
                    break;
                case 1:
                     recive_box.Text += "\r\nNo Tag";
                    break;
                case 2:
                    recive_box.Text += "\r\nLogin to a sector successfully";

                    break;
                case 3:
                    recive_box.Text += "\r\nLogin to a sector fail";
                    break;
                case 4:
                    recive_box.Text += "\r\nRead a data block fail";
                    break;
                case 5:
                    recive_box.Text += "\r\nWrite a data block fail";
                    break;
                case 6:
                    recive_box.Text += "\r\nUnable to read after write";
                    break;
                case 0x0D:
                    recive_box.Text += "\r\nNot authenticate";
                    break;
                case 0x0E:
                    recive_box.Text += "\r\nNot a value block";
                    dataBox.Text = "";
                    break;
                case 0xF0:
                    recive_box.Text += "\r\nChecksum Error";
                    break;
                case 0xF1:
                    recive_box.Text += "\r\nCommand code Error";
                    break;
            }
         }
        void card_type(byte rec_)
        {
            switch (rec_)
            { 
                case 1:
                    recive_box.Text += "\r\nCard Type Standard Mifare 1K Card";
                    break;
                case 3:
                    recive_box.Text += "\r\nCard Type Mifare UltraLight Card";
                    break;
                case 4:
                    recive_box.Text += "\r\nCard Type Standard Mifare 4K Card";
                    break;
                case 7:
                    recive_box.Text += "\r\nCard Type Standard Mifare Mini 320Byte Card";
                    break;
                default :
                    recive_box.Text += "\r\nCard Type Not support";
                    break;
            }
        }
        private void show_ID_card(byte[] show)
        {
            recive_box.Text += "\r\nSerial Number =";
            for (int i = 4; i < show.Length - 2; i++)
            {
                recive_box.Text += Convert.ToString(show[i], 16).PadLeft(2, '0').PadRight(3, ' ').ToUpper();
            }
        }
        
        private void Form1_Load(object sender, EventArgs e)
        {
            string[] s = SerialPort.GetPortNames();
            int i = 0;

            baud_list.Items.Clear();
            baud_list.Items.Add("1200");
            baud_list.Items.Add("2400");
            baud_list.Items.Add("4800");
            baud_list.Items.Add("9600");
            baud_list.Items.Add("19200");
            baud_list.Items.Add("38400");
            baud_list.Items.Add("57600");
            baud_list.Items.Add("115200");
            baud_list.Items.Add("230400");
            baud_list.SelectedIndex = 3;
            list_port.Items.Clear();
            
            foreach (string port in s)
            {
                list_port.Items.Add(s[i]);
                i++;
            }
            list_port.SelectedIndex = 0;
        }
        private void con_dis_Click(object sender, EventArgs e)
        {
            if (list_port.Items.Count > 0) // If there are ports available
            {
                    serialPort.BaudRate = int.Parse(baud_list.Text);
                    serialPort.DataBits = 8;
                    serialPort.Parity = (Parity)Enum.Parse(typeof(Parity), "None");
                    serialPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), "One");
                    serialPort.PortName = list_port.Text;
                    serialPort.Open();
                    groupBox1.Enabled = true;   
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            protocal(Select_Card,null);
        }
       

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Close();
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            byte[] dat_login = new  byte[10];

            
            if ((sectorBox.Text.Length > 0)&&(keyBox.Text.Length>0))
            {       
                    if (keyBox.Text == "KeyA")
                    {
                        dat_login[0] = 0xAA;
                    }
                    else if (keyBox.Text == "KeyB")
                    {
                        dat_login[0] = 0xBB;
                    }
                    else
                    {
                        MessageBox.Show("Error Please Select Type ");
                    }
                    check_key_box();
                    check_key_box();
                    dat_login[1] = str_to_byte(key1.Text);
                    dat_login[2] = str_to_byte(key2.Text);
                    dat_login[3] = str_to_byte(key3.Text);
                    dat_login[4] = str_to_byte(key4.Text);
                    dat_login[5] = str_to_byte(key5.Text);
                    dat_login[6] = str_to_byte(key6.Text);
                    protocal(Login, dat_login);
            }
            else
                MessageBox.Show("Error");
        }
        byte str_to_byte (string str_key)
        {
            char[] data = str_key.ToCharArray();
            int len = data.Length;
            int[] num = new Int32[len];
            int fg = 1;

            for (int i = 0; i < len; i++)
            {
                if ((data[i] >= '0') || (data[i] <= '9'))
                {
                    num[i] = (Convert.ToInt32(data[i])) - 0x30;

                }
                if ((data[i] >= 'A') || (data[i] <= 'F'))
                {
                    switch (data[i])
                    {
                        case 'A':
                            num[i] = 10;
                            break;
                        case 'B':
                            num[i] = 11;
                            break;
                        case 'C':
                            num[i] = 12;
                            break;
                        case 'D':
                            num[i] = 13;
                            break;
                        case 'E':
                            num[i] = 14;
                            break;
                        case 'F':
                            num[i] = 15;
                            break;
                    }
                }
            }
            for (int i = 0; i < len; i++)
            {
                if ((num[i] > 15) || (num[i] < 0))
                {
                    MessageBox.Show("Please Key HEX");
                    fg = 0;
                }
            }
            if (fg == 1)
            {
                return _to_byte(num)[0];
            }
            return 0;
        }

        byte[] _to_byte(int[] in_byte)
        {

            int len = in_byte.Length;
            
            byte[] _byte_buf = new byte[len / 2];
            byte a;
            int j = 0;

            for (int i = 0; i < len / 2; i++)
            {
                a = Convert.ToByte(in_byte[j] << 4);
                j++;
                a |= Convert.ToByte(in_byte[j]);
                j++;
                _byte_buf[i] = a;

            }
            return _byte_buf;
        }
        
        void check_key_box()
        {
            string buf;
           
            if (key1.Text.Length < 2)
            {
                buf = key1.Text;
                key1.Text = "0";
                key1.Text += buf;
            }
            if (key2.Text.Length < 2)
            {
                buf = key2.Text;
                key2.Text = "0";
                key2.Text += buf;
            }
            if (key3.Text.Length < 2)
            {
                buf = key3.Text;
                key3.Text = "0";
                key3.Text += buf;
            }
            if (key4.Text.Length < 2)
            {
                buf = key4.Text;
                key4.Text = "0";
                key4.Text += buf;
            }
            if (key5.Text.Length < 2)
            {
                buf = key5.Text;
                key5.Text = "0";
                key5.Text += buf;
            }
            if (key6.Text.Length < 2)
            {
                buf = key6.Text;
                key6.Text = "0";
                key6.Text += buf;
            }
            
        }
        void check_key_write()
        {
            string buf;

            if (write1.Text.Length < 2)
            {
                buf = write1.Text;
                write1.Text = "0";
                write1.Text += buf;
            }
            if (write2.Text.Length < 2)
            {
                buf = write2.Text;
                write2.Text = "0";
                write2.Text += buf;
            }
            if (write3.Text.Length < 2)
            {
                buf = write3.Text;
                write3.Text = "0";
                write3.Text += buf;
            }
            if (write4.Text.Length < 2)
            {
                buf = write4.Text;
                write4.Text = "0";
                write4.Text += buf;
            }
            if (write5.Text.Length < 2)
            {
                buf = write5.Text;
                write5.Text = "0";
                write5.Text += buf;
            }
            if (write6.Text.Length < 2)
            {
                buf = write6.Text;
                write6.Text = "0";
                write6.Text += buf;
            }
            if (write7.Text.Length < 2)
            {
                buf = write7.Text;
                write7.Text = "0";
                write7.Text += buf;
            }
            if (write8.Text.Length < 2)
            {
                buf = write8.Text;
                write8.Text = "0";
                write8.Text += buf;
            }
            if (write9.Text.Length < 2)
            {
                buf = write9.Text;
                write9.Text = "0";
                write9.Text += buf;
            }
            if (write10.Text.Length < 2)
            {
                buf = write10.Text;
                write10.Text = "0";
                write10.Text += buf;
            }
            if (write11.Text.Length < 2)
            {
                buf = write11.Text;
                write11.Text = "0";
                write11.Text += buf;
            }
            if (write12.Text.Length < 2)
            {
                buf = write12.Text;
                write12.Text = "0";
                write12.Text += buf;
            }
            if (write13.Text.Length < 2)
            {
                buf = write13.Text;
                write13.Text = "0";
                write13.Text += buf;
            }
            if (write14.Text.Length < 2)
            {
                buf = write14.Text;
                write14.Text = "0";
                write14.Text += buf;
            }
            if (write15.Text.Length < 2)
            {
                buf = write15.Text;
                write15.Text = "0";
                write15.Text += buf;
            }
            if (write16.Text.Length < 2)
            {
                buf = write16.Text;
                write16.Text = "0";
                write16.Text += buf;
            }

        
        }
      
        private void button3_Click(object sender, EventArgs e)
        {
            if (ReadDataBlock.Checked)
            {
                protocal(Read_data_block, null);
            }
            if (Readvalueblock.Checked)
            {
                protocal(Read_value_block, null);
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (serialPort.IsOpen)
            {
                serialPort.Close(); // Close port
                groupBox1.Enabled = false;
            }
        }

        void update_sendBox(byte[] send_dat)
        {
            switch (send_dat[2])
            { 
                case Select_Card:
                    send_box.Text  = "Select Card\r\n";
                    
                break;

                case Login:
                send_box.Text = "LOGIN TO A SECTER\r\n";
                break;
                
                case Read_data_block:
                send_box.Text = "READ A DATA BLOCK\r\n";
                break;

                case Write_data_block:
                send_box.Text = "WRITE A DATA BLOCK\r\n";
                break;

                case Read_value_block:
                send_box.Text = "READ A VALUE BLOCK\r\n";
                break;
                
                case Write_value_block:
                send_box.Text = "WRITE A VALUE BLOCK\r\n";
                break;
                
                case Increment:
                send_box.Text = "INCREMENT A VALUE BLOCK\r\n";
                break;
                
                case Decrement:
                send_box.Text = "DECREMENT A VALUE BLOCK\r\n";
                break;

                case Control_led:
                send_box.Text = "CONTROL THE LED\r\n";
                break;

                case Write_master_keyA:
                send_box.Text = "Write Master key (key A)\r\n";
                break;


            }
            for (int cnt = 0; cnt < (send_dat[1]+2); cnt++)
            {
                if (send_dat[cnt] < 16)
                {
                    send_box.Text += "0";
                }
                send_box.Text += Convert.ToString(send_dat[cnt],16).ToUpper();
                send_box.Text += " ";
            }
        }
        void protocal(byte cmd, byte[] data)
        {
            byte[] send_byte = new byte[30];
            send_byte[0] = Header;
            int temp_sector = 0;
            int sector=0, block=0;
            sector = int.Parse(sectorBox.Text);
            block = int.Parse(block_combo.Text);
            temp_sector = block + (sector * 4);

            
            switch (cmd)
            {
                case Select_Card :
                    
                    send_byte[1] = 2;
                    send_byte[2] = Select_Card;
                    send_byte[3] = cal_chk(send_byte,mode_send);
                    send_out_(send_byte);
                    break;
                case Login:
                    
                    send_byte[1] = 10;
                    send_byte[2] = Login;
                    send_byte[3] = byte.Parse(sectorBox.Text);
                    for (int i = 0; i < send_byte[1] - 3; i++)
                    {
                        send_byte[4 + i] = data[i];
                    }
                    send_byte[11] = cal_chk(send_byte, mode_send);
                    send_out_(send_byte);
                    break;
                case Read_data_block:
                    send_byte[1] = 3;
                    send_byte[2] = Read_data_block;
                    send_byte[3] = Convert.ToByte(temp_sector);
                    send_byte[4] = cal_chk(send_byte,mode_send);
                    send_out_(send_byte);
                    break;
                case Write_data_block:
                    send_byte[1] = 19;
                    send_byte[2] = Write_data_block;
                    for (int cnt = 0; cnt <= 16; cnt++)
                    {
                        send_byte[3 + cnt] = data[cnt];
                    }
                    send_byte[20] = cal_chk(send_byte, mode_send);
                    send_out_(send_byte);
                    break;
                case Read_value_block:
                    
                        send_byte[1] = 3;
                        send_byte[2] = Read_value_block;
                        send_byte[3] = Convert.ToByte(temp_sector);
                        send_byte[4] = cal_chk(send_byte, mode_send);
                        send_out_(send_byte);
                     break;
                case Write_value_block:
                        send_byte[1] = 7;
                        send_byte[2] = Write_value_block;
                        for (int cnt = 0; cnt <= 5; cnt++)
                        {
                             send_byte[3 + cnt] = data[cnt];
                        }
                        send_byte[8] = cal_chk(send_byte, mode_send);
                        send_out_(send_byte);
                     break;
                case Increment:
                     send_byte[1] = 7;
                     send_byte[2] = Increment;
                     for (int cnt = 0; cnt <= 5; cnt++)
                     {
                         send_byte[3 + cnt] = data[cnt];
                     }
                     send_byte[8] = cal_chk(send_byte, mode_send);
                     send_out_(send_byte);
                     break;
                case Decrement:
                     send_byte[1] = 7;
                     send_byte[2] = Decrement;
                     for (int cnt = 0; cnt <= 5; cnt++)
                     {
                         send_byte[3 + cnt] = data[cnt];
                     }
                     send_byte[8] = cal_chk(send_byte, mode_send);
                     send_out_(send_byte);
                     break;
                case Control_led:
                     send_byte[1] = 3;
                     send_byte[2] = Control_led;
                     send_byte[3] = data[0];
                     send_byte[4] = cal_chk(send_byte, mode_send);
                     send_out_(send_byte);
                    break;
                case Write_master_keyA:
                    send_byte[1] = 9;
                    send_byte[2] = Write_master_keyA;
                    for (int i = 0; i < send_byte[1] - 2; i++)
                    {
                        send_byte[3 + i] = data[i];
                    }
                    send_byte[10] = cal_chk(send_byte, mode_send);
                    send_out_(send_byte);
                    break;


            }

        }
        byte cal_chk(byte[] cal_sum,int mode)
        {
            Int32 chk=0;
            if (mode == mode_send)
                chk = Header;
            else
                chk = Header_rec;
            
            for (int cnt = 1; cnt < cal_sum[1] + mode; cnt++)
            {
                chk = chk ^ cal_sum[cnt];
            }
                return Convert.ToByte(chk);
        }
        void send_out_(byte[] out_)
        {
            update_sendBox(out_);
            serialPort.Write(out_, 0, out_[1]+2);
            
        }

        private void bt_write_Click(object sender, EventArgs e)
        {   
            byte[] dat_write = new byte[20];
            check_key_write();
            check_key_write();
            int cal_block=0;
            int sector, block;
            if(Block_write.Text.Length>0)
            {
                try
                {
                    block = int.Parse(Block_write.Text);
                    sector = int.Parse(sectorBox.Text);
                    cal_block = block + (sector * 4);
                    dat_write[0] = Convert.ToByte(cal_block);
                }
                catch
                {
                    MessageBox.Show("Error Block");
                }
                if (Writedatablock_radio.Checked)
                {
                    dat_write[1] = str_to_byte(write1.Text);
                    dat_write[2] = str_to_byte(write2.Text);
                    dat_write[3] = str_to_byte(write3.Text);
                    dat_write[4] = str_to_byte(write4.Text);
                    dat_write[5] = str_to_byte(write5.Text);
                    dat_write[6] = str_to_byte(write6.Text);
                    dat_write[7] = str_to_byte(write7.Text);
                    dat_write[8] = str_to_byte(write8.Text);
                    dat_write[9] = str_to_byte(write9.Text);
                    dat_write[10] = str_to_byte(write10.Text);
                    dat_write[11] = str_to_byte(write11.Text);
                    dat_write[12] = str_to_byte(write12.Text);
                    dat_write[13] = str_to_byte(write13.Text);
                    dat_write[14] = str_to_byte(write14.Text);
                    dat_write[15] = str_to_byte(write15.Text);
                    dat_write[16] = str_to_byte(write16.Text);
                    protocal(Write_data_block, dat_write); 
                }
                else
                {
                    dat_write[1] = str_to_byte(write1.Text);
                    dat_write[2] = str_to_byte(write2.Text);
                    dat_write[3] = str_to_byte(write3.Text);
                    dat_write[4] = str_to_byte(write4.Text);
                    if (Writevalueblock_radio.Checked)
                        protocal(Write_value_block, dat_write);
                    if (INCREMENTradio.Checked)
                        protocal(Increment, dat_write);
                    if (DECREMENTradio.Checked)
                        protocal(Decrement, dat_write);
                }
                 
            }
        }

        private void Writedatablock_radio_CheckedChanged(object sender, EventArgs e)
        {
            write1.Enabled = true;
            write2.Enabled = true;
            write3.Enabled = true;
            write4.Enabled = true;
            write5.Enabled = true;
            write6.Enabled = true;
            write7.Enabled = true;
            write8.Enabled = true;
            write9.Enabled = true;
            write10.Enabled = true;
            write11.Enabled = true;
            write12.Enabled = true;
            write13.Enabled = true;
            write14.Enabled = true; 
            write15.Enabled = true; 
            write16.Enabled = true;
        }

        private void Writevalueblock_radio_CheckedChanged(object sender, EventArgs e)
        {
            key_4byte();
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            key_4byte();
        }
        void key_4byte()
        {
            write1.Enabled = true;
            write2.Enabled = true;
            write3.Enabled = true;
            write4.Enabled = true;
            write5.Enabled = false;
            write6.Enabled = false;
            write7.Enabled = false;
            write8.Enabled = false;
            write9.Enabled = false;
            write10.Enabled = false;
            write11.Enabled = false;
            write12.Enabled = false;
            write13.Enabled = false;
            write14.Enabled = false;
            write15.Enabled = false;
            write16.Enabled = false;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            key_4byte();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            byte[] status = new byte[2];
            status[0]=1;
            protocal(Control_led,status);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            byte[] status = new byte[2];
            status[0] = 0;
            protocal(Control_led, status);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            
            byte[] dat_write = new byte[8];
            check_new_key_write();
            check_new_key_write();
            if (sectorBox.Text.Length > 0)
            {
                try
                {
                    dat_write[0] = byte.Parse(sectorBox.Text);
                }
                catch
                { 
                    MessageBox.Show("Error Sector Block");
                }
                dat_write[1] = str_to_byte(n_key1.Text);
                dat_write[2] = str_to_byte(n_key2.Text);
                dat_write[3] = str_to_byte(n_key3.Text);
                dat_write[4] = str_to_byte(n_key4.Text);
                dat_write[5] = str_to_byte(n_key5.Text);
                dat_write[6] = str_to_byte(n_key6.Text);
                protocal(Write_master_keyA, dat_write);
            }
            else
            {
                MessageBox.Show("Error Sector Block");
            }

            


        }
        void check_new_key_write()
        {
            string buf;

            if (n_key1.Text.Length < 2)
            {
                buf = n_key1.Text;
                n_key1.Text = "0";
                n_key1.Text += buf;
            }
            if (n_key2.Text.Length < 2)
            {
                buf = n_key2.Text;
                n_key2.Text = "0";
                n_key2.Text += buf;
            }
            if (n_key3.Text.Length < 2)
            {
                buf = n_key3.Text;
                n_key3.Text = "0";
                n_key3.Text += buf;
            }
            if (n_key4.Text.Length < 2)
            {
                buf = n_key4.Text;
                n_key4.Text = "0";
                n_key4.Text += buf;
            }
            if (n_key5.Text.Length < 2)
            {
                buf = n_key5.Text;
                n_key5.Text = "0";
                n_key5.Text += buf;
            }
            if (n_key6.Text.Length < 2)
            {
                buf = n_key6.Text;
                n_key6.Text = "0";
                n_key6.Text += buf;
            }
        }

    }
}
