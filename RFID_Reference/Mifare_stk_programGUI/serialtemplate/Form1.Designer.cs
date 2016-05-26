namespace serialtemplate
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.con_dis = new System.Windows.Forms.Button();
            this.list_port = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.baud_list = new System.Windows.Forms.ComboBox();
            this.serialPort = new System.IO.Ports.SerialPort(this.components);
            this.recive_box = new System.Windows.Forms.TextBox();
            this.button4 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.send_box = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.button7 = new System.Windows.Forms.Button();
            this.n_key3 = new System.Windows.Forms.TextBox();
            this.n_key6 = new System.Windows.Forms.TextBox();
            this.n_key1 = new System.Windows.Forms.TextBox();
            this.n_key4 = new System.Windows.Forms.TextBox();
            this.n_key2 = new System.Windows.Forms.TextBox();
            this.n_key5 = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.button6 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.write = new System.Windows.Forms.GroupBox();
            this.DECREMENTradio = new System.Windows.Forms.RadioButton();
            this.INCREMENTradio = new System.Windows.Forms.RadioButton();
            this.Writevalueblock_radio = new System.Windows.Forms.RadioButton();
            this.Writedatablock_radio = new System.Windows.Forms.RadioButton();
            this.label9 = new System.Windows.Forms.Label();
            this.Block_write = new System.Windows.Forms.ComboBox();
            this.bt_write = new System.Windows.Forms.Button();
            this.write16 = new System.Windows.Forms.TextBox();
            this.write15 = new System.Windows.Forms.TextBox();
            this.write14 = new System.Windows.Forms.TextBox();
            this.write13 = new System.Windows.Forms.TextBox();
            this.write12 = new System.Windows.Forms.TextBox();
            this.write11 = new System.Windows.Forms.TextBox();
            this.write9 = new System.Windows.Forms.TextBox();
            this.write10 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.write4 = new System.Windows.Forms.TextBox();
            this.write8 = new System.Windows.Forms.TextBox();
            this.write2 = new System.Windows.Forms.TextBox();
            this.write7 = new System.Windows.Forms.TextBox();
            this.write1 = new System.Windows.Forms.TextBox();
            this.write6 = new System.Windows.Forms.TextBox();
            this.write3 = new System.Windows.Forms.TextBox();
            this.write5 = new System.Windows.Forms.TextBox();
            this.read = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.Readvalueblock = new System.Windows.Forms.RadioButton();
            this.ReadDataBlock = new System.Windows.Forms.RadioButton();
            this.datat = new System.Windows.Forms.Label();
            this.dataBox = new System.Windows.Forms.TextBox();
            this.block_combo = new System.Windows.Forms.ComboBox();
            this.login = new System.Windows.Forms.GroupBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.key6 = new System.Windows.Forms.TextBox();
            this.keyBox = new System.Windows.Forms.ComboBox();
            this.key5 = new System.Windows.Forms.TextBox();
            this.key4 = new System.Windows.Forms.TextBox();
            this.sectorBox = new System.Windows.Forms.ComboBox();
            this.key3 = new System.Windows.Forms.TextBox();
            this.key1 = new System.Windows.Forms.TextBox();
            this.key2 = new System.Windows.Forms.TextBox();
            this.select = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.write.SuspendLayout();
            this.read.SuspendLayout();
            this.login.SuspendLayout();
            this.select.SuspendLayout();
            this.SuspendLayout();
            // 
            // con_dis
            // 
            this.con_dis.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(222)));
            this.con_dis.Location = new System.Drawing.Point(217, 12);
            this.con_dis.Name = "con_dis";
            this.con_dis.Size = new System.Drawing.Size(97, 35);
            this.con_dis.TabIndex = 0;
            this.con_dis.Text = "Connect";
            this.con_dis.UseVisualStyleBackColor = true;
            this.con_dis.Click += new System.EventHandler(this.con_dis_Click);
            // 
            // list_port
            // 
            this.list_port.FormattingEnabled = true;
            this.list_port.Location = new System.Drawing.Point(69, 20);
            this.list_port.Name = "list_port";
            this.list_port.Size = new System.Drawing.Size(140, 21);
            this.list_port.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(7, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(54, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "ComPort";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Baudrate";
            // 
            // baud_list
            // 
            this.baud_list.FormattingEnabled = true;
            this.baud_list.Location = new System.Drawing.Point(69, 55);
            this.baud_list.Name = "baud_list";
            this.baud_list.Size = new System.Drawing.Size(140, 21);
            this.baud_list.TabIndex = 4;
            // 
            // serialPort
            // 
            this.serialPort.ReadBufferSize = 2048;
            this.serialPort.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_DataReceived);
            // 
            // recive_box
            // 
            this.recive_box.Location = new System.Drawing.Point(807, 21);
            this.recive_box.Multiline = true;
            this.recive_box.Name = "recive_box";
            this.recive_box.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.recive_box.Size = new System.Drawing.Size(336, 87);
            this.recive_box.TabIndex = 6;
            // 
            // button4
            // 
            this.button4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(222)));
            this.button4.Location = new System.Drawing.Point(217, 53);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(97, 35);
            this.button4.TabIndex = 9;
            this.button4.Text = "Disconnect";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(222)));
            this.label3.ForeColor = System.Drawing.Color.Red;
            this.label3.Location = new System.Drawing.Point(754, 37);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 13);
            this.label3.TabIndex = 11;
            this.label3.Text = "Recive";
            // 
            // send_box
            // 
            this.send_box.Location = new System.Drawing.Point(380, 21);
            this.send_box.Multiline = true;
            this.send_box.Name = "send_box";
            this.send_box.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.send_box.Size = new System.Drawing.Size(336, 87);
            this.send_box.TabIndex = 12;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(222)));
            this.label4.ForeColor = System.Drawing.Color.Blue;
            this.label4.Location = new System.Drawing.Point(337, 41);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(36, 13);
            this.label4.TabIndex = 13;
            this.label4.Text = "Send";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(170, 17);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(143, 28);
            this.button1.TabIndex = 5;
            this.button1.Text = "Select Card";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(145, 132);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(104, 28);
            this.button2.TabIndex = 7;
            this.button2.Text = "Login ";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(186, 58);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(169, 28);
            this.button3.TabIndex = 8;
            this.button3.Text = "Read";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.groupBox4);
            this.groupBox1.Controls.Add(this.pictureBox1);
            this.groupBox1.Controls.Add(this.groupBox3);
            this.groupBox1.Controls.Add(this.write);
            this.groupBox1.Controls.Add(this.read);
            this.groupBox1.Controls.Add(this.login);
            this.groupBox1.Controls.Add(this.select);
            this.groupBox1.Enabled = false;
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(222)));
            this.groupBox1.Location = new System.Drawing.Point(14, 114);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(1129, 436);
            this.groupBox1.TabIndex = 10;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Control Group";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.button7);
            this.groupBox4.Controls.Add(this.n_key3);
            this.groupBox4.Controls.Add(this.n_key6);
            this.groupBox4.Controls.Add(this.n_key1);
            this.groupBox4.Controls.Add(this.n_key4);
            this.groupBox4.Controls.Add(this.n_key2);
            this.groupBox4.Controls.Add(this.n_key5);
            this.groupBox4.Controls.Add(this.label12);
            this.groupBox4.Location = new System.Drawing.Point(485, 255);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(482, 89);
            this.groupBox4.TabIndex = 15;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Write master key (key A)";
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(420, 31);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(56, 39);
            this.button7.TabIndex = 52;
            this.button7.Text = "Write";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // n_key3
            // 
            this.n_key3.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.n_key3.Location = new System.Drawing.Point(241, 39);
            this.n_key3.MaxLength = 2;
            this.n_key3.Name = "n_key3";
            this.n_key3.Size = new System.Drawing.Size(34, 24);
            this.n_key3.TabIndex = 46;
            this.n_key3.Text = "FF";
            this.n_key3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // n_key6
            // 
            this.n_key6.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.n_key6.Location = new System.Drawing.Point(367, 39);
            this.n_key6.MaxLength = 2;
            this.n_key6.Name = "n_key6";
            this.n_key6.Size = new System.Drawing.Size(34, 24);
            this.n_key6.TabIndex = 51;
            this.n_key6.Text = "FF";
            this.n_key6.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // n_key1
            // 
            this.n_key1.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.n_key1.Location = new System.Drawing.Point(157, 39);
            this.n_key1.MaxLength = 2;
            this.n_key1.Name = "n_key1";
            this.n_key1.Size = new System.Drawing.Size(34, 24);
            this.n_key1.TabIndex = 44;
            this.n_key1.Text = "FF";
            this.n_key1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // n_key4
            // 
            this.n_key4.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.n_key4.Location = new System.Drawing.Point(283, 39);
            this.n_key4.MaxLength = 2;
            this.n_key4.Name = "n_key4";
            this.n_key4.Size = new System.Drawing.Size(34, 24);
            this.n_key4.TabIndex = 49;
            this.n_key4.Text = "FF";
            this.n_key4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // n_key2
            // 
            this.n_key2.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.n_key2.Location = new System.Drawing.Point(199, 39);
            this.n_key2.MaxLength = 2;
            this.n_key2.Name = "n_key2";
            this.n_key2.Size = new System.Drawing.Size(34, 24);
            this.n_key2.TabIndex = 45;
            this.n_key2.Text = "FF";
            this.n_key2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // n_key5
            // 
            this.n_key5.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.n_key5.Location = new System.Drawing.Point(325, 39);
            this.n_key5.MaxLength = 2;
            this.n_key5.Name = "n_key5";
            this.n_key5.Size = new System.Drawing.Size(34, 24);
            this.n_key5.TabIndex = 50;
            this.n_key5.Text = "FF";
            this.n_key5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(64, 42);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(86, 18);
            this.label12.TabIndex = 48;
            this.label12.Text = "KEY(HEX)";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::serialtemplate.Properties.Resources.Logo;
            this.pictureBox1.Location = new System.Drawing.Point(977, 243);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(166, 185);
            this.pictureBox1.TabIndex = 14;
            this.pictureBox1.TabStop = false;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.button6);
            this.groupBox3.Controls.Add(this.button5);
            this.groupBox3.Location = new System.Drawing.Point(488, 347);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(480, 76);
            this.groupBox3.TabIndex = 13;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "LED Control";
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(256, 25);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(123, 35);
            this.button6.TabIndex = 1;
            this.button6.Text = "LED OFF";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Click += new System.EventHandler(this.button6_Click);
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(87, 25);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(123, 35);
            this.button5.TabIndex = 0;
            this.button5.Text = "LED ON";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.button5_Click);
            // 
            // write
            // 
            this.write.Controls.Add(this.DECREMENTradio);
            this.write.Controls.Add(this.INCREMENTradio);
            this.write.Controls.Add(this.Writevalueblock_radio);
            this.write.Controls.Add(this.Writedatablock_radio);
            this.write.Controls.Add(this.label9);
            this.write.Controls.Add(this.Block_write);
            this.write.Controls.Add(this.bt_write);
            this.write.Controls.Add(this.write16);
            this.write.Controls.Add(this.write15);
            this.write.Controls.Add(this.write14);
            this.write.Controls.Add(this.write13);
            this.write.Controls.Add(this.write12);
            this.write.Controls.Add(this.write11);
            this.write.Controls.Add(this.write9);
            this.write.Controls.Add(this.write10);
            this.write.Controls.Add(this.label8);
            this.write.Controls.Add(this.write4);
            this.write.Controls.Add(this.write8);
            this.write.Controls.Add(this.write2);
            this.write.Controls.Add(this.write7);
            this.write.Controls.Add(this.write1);
            this.write.Controls.Add(this.write6);
            this.write.Controls.Add(this.write3);
            this.write.Controls.Add(this.write5);
            this.write.Location = new System.Drawing.Point(485, 33);
            this.write.Name = "write";
            this.write.Size = new System.Drawing.Size(483, 219);
            this.write.TabIndex = 12;
            this.write.TabStop = false;
            this.write.Text = "Write";
            // 
            // DECREMENTradio
            // 
            this.DECREMENTradio.AutoSize = true;
            this.DECREMENTradio.Location = new System.Drawing.Point(217, 56);
            this.DECREMENTradio.Name = "DECREMENTradio";
            this.DECREMENTradio.Size = new System.Drawing.Size(264, 22);
            this.DECREMENTradio.TabIndex = 43;
            this.DECREMENTradio.Text = "DECREMENT A VALUE BLOCK";
            this.DECREMENTradio.UseVisualStyleBackColor = true;
            this.DECREMENTradio.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // INCREMENTradio
            // 
            this.INCREMENTradio.AutoSize = true;
            this.INCREMENTradio.Location = new System.Drawing.Point(216, 31);
            this.INCREMENTradio.Name = "INCREMENTradio";
            this.INCREMENTradio.Size = new System.Drawing.Size(257, 22);
            this.INCREMENTradio.TabIndex = 42;
            this.INCREMENTradio.Text = "INCREMENT A VALUE BLOCK";
            this.INCREMENTradio.UseVisualStyleBackColor = true;
            this.INCREMENTradio.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // Writevalueblock_radio
            // 
            this.Writevalueblock_radio.AutoSize = true;
            this.Writevalueblock_radio.Location = new System.Drawing.Point(27, 55);
            this.Writevalueblock_radio.Name = "Writevalueblock_radio";
            this.Writevalueblock_radio.Size = new System.Drawing.Size(170, 22);
            this.Writevalueblock_radio.TabIndex = 41;
            this.Writevalueblock_radio.Text = "Write a value block";
            this.Writevalueblock_radio.UseVisualStyleBackColor = true;
            this.Writevalueblock_radio.CheckedChanged += new System.EventHandler(this.Writevalueblock_radio_CheckedChanged);
            // 
            // Writedatablock_radio
            // 
            this.Writedatablock_radio.AutoSize = true;
            this.Writedatablock_radio.Checked = true;
            this.Writedatablock_radio.Location = new System.Drawing.Point(27, 31);
            this.Writedatablock_radio.Name = "Writedatablock_radio";
            this.Writedatablock_radio.Size = new System.Drawing.Size(163, 22);
            this.Writedatablock_radio.TabIndex = 40;
            this.Writedatablock_radio.TabStop = true;
            this.Writedatablock_radio.Text = "Write a data block";
            this.Writedatablock_radio.UseVisualStyleBackColor = true;
            this.Writedatablock_radio.CheckedChanged += new System.EventHandler(this.Writedatablock_radio_CheckedChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(18, 98);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(51, 18);
            this.label9.TabIndex = 39;
            this.label9.Text = "Block";
            // 
            // Block_write
            // 
            this.Block_write.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3"});
            this.Block_write.Location = new System.Drawing.Point(27, 119);
            this.Block_write.Name = "Block_write";
            this.Block_write.Size = new System.Drawing.Size(33, 26);
            this.Block_write.TabIndex = 25;
            this.Block_write.Text = "0";
            // 
            // bt_write
            // 
            this.bt_write.Location = new System.Drawing.Point(188, 175);
            this.bt_write.Name = "bt_write";
            this.bt_write.Size = new System.Drawing.Size(105, 33);
            this.bt_write.TabIndex = 38;
            this.bt_write.Text = "Write";
            this.bt_write.UseVisualStyleBackColor = true;
            this.bt_write.Click += new System.EventHandler(this.bt_write_Click);
            // 
            // write16
            // 
            this.write16.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write16.Location = new System.Drawing.Point(385, 139);
            this.write16.MaxLength = 2;
            this.write16.Name = "write16";
            this.write16.Size = new System.Drawing.Size(34, 24);
            this.write16.TabIndex = 37;
            this.write16.Text = "FF";
            this.write16.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write15
            // 
            this.write15.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write15.Location = new System.Drawing.Point(343, 139);
            this.write15.MaxLength = 2;
            this.write15.Name = "write15";
            this.write15.Size = new System.Drawing.Size(34, 24);
            this.write15.TabIndex = 36;
            this.write15.Text = "FF";
            this.write15.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write14
            // 
            this.write14.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write14.Location = new System.Drawing.Point(301, 139);
            this.write14.MaxLength = 2;
            this.write14.Name = "write14";
            this.write14.Size = new System.Drawing.Size(34, 24);
            this.write14.TabIndex = 35;
            this.write14.Text = "FF";
            this.write14.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write13
            // 
            this.write13.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write13.Location = new System.Drawing.Point(259, 139);
            this.write13.MaxLength = 2;
            this.write13.Name = "write13";
            this.write13.Size = new System.Drawing.Size(34, 24);
            this.write13.TabIndex = 34;
            this.write13.Text = "FF";
            this.write13.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write12
            // 
            this.write12.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write12.Location = new System.Drawing.Point(217, 139);
            this.write12.MaxLength = 2;
            this.write12.Name = "write12";
            this.write12.Size = new System.Drawing.Size(34, 24);
            this.write12.TabIndex = 33;
            this.write12.Text = "FF";
            this.write12.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write11
            // 
            this.write11.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write11.Location = new System.Drawing.Point(175, 139);
            this.write11.MaxLength = 2;
            this.write11.Name = "write11";
            this.write11.Size = new System.Drawing.Size(34, 24);
            this.write11.TabIndex = 32;
            this.write11.Text = "FF";
            this.write11.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write9
            // 
            this.write9.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write9.Location = new System.Drawing.Point(91, 139);
            this.write9.MaxLength = 2;
            this.write9.Name = "write9";
            this.write9.Size = new System.Drawing.Size(34, 24);
            this.write9.TabIndex = 30;
            this.write9.Text = "FF";
            this.write9.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write10
            // 
            this.write10.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write10.Location = new System.Drawing.Point(133, 139);
            this.write10.MaxLength = 2;
            this.write10.Name = "write10";
            this.write10.Size = new System.Drawing.Size(34, 24);
            this.write10.TabIndex = 31;
            this.write10.Text = "FF";
            this.write10.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(192, 82);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(94, 18);
            this.label8.TabIndex = 29;
            this.label8.Text = "Data (HEX)";
            // 
            // write4
            // 
            this.write4.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write4.Location = new System.Drawing.Point(216, 107);
            this.write4.MaxLength = 2;
            this.write4.Name = "write4";
            this.write4.Size = new System.Drawing.Size(34, 24);
            this.write4.TabIndex = 24;
            this.write4.Text = "FF";
            this.write4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write8
            // 
            this.write8.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write8.Location = new System.Drawing.Point(384, 107);
            this.write8.MaxLength = 2;
            this.write8.Name = "write8";
            this.write8.Size = new System.Drawing.Size(34, 24);
            this.write8.TabIndex = 28;
            this.write8.Text = "FF";
            this.write8.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write2
            // 
            this.write2.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write2.Location = new System.Drawing.Point(132, 107);
            this.write2.MaxLength = 2;
            this.write2.Name = "write2";
            this.write2.Size = new System.Drawing.Size(34, 24);
            this.write2.TabIndex = 22;
            this.write2.Text = "FF";
            this.write2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write7
            // 
            this.write7.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write7.Location = new System.Drawing.Point(342, 107);
            this.write7.MaxLength = 2;
            this.write7.Name = "write7";
            this.write7.Size = new System.Drawing.Size(34, 24);
            this.write7.TabIndex = 27;
            this.write7.Text = "FF";
            this.write7.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write1
            // 
            this.write1.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write1.Location = new System.Drawing.Point(90, 107);
            this.write1.MaxLength = 2;
            this.write1.Name = "write1";
            this.write1.Size = new System.Drawing.Size(34, 24);
            this.write1.TabIndex = 21;
            this.write1.Text = "FF";
            this.write1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write6
            // 
            this.write6.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write6.Location = new System.Drawing.Point(300, 107);
            this.write6.MaxLength = 2;
            this.write6.Name = "write6";
            this.write6.Size = new System.Drawing.Size(34, 24);
            this.write6.TabIndex = 26;
            this.write6.Text = "FF";
            this.write6.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write3
            // 
            this.write3.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write3.Location = new System.Drawing.Point(174, 107);
            this.write3.MaxLength = 2;
            this.write3.Name = "write3";
            this.write3.Size = new System.Drawing.Size(34, 24);
            this.write3.TabIndex = 23;
            this.write3.Text = "FF";
            this.write3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // write5
            // 
            this.write5.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.write5.Location = new System.Drawing.Point(258, 107);
            this.write5.MaxLength = 2;
            this.write5.Name = "write5";
            this.write5.Size = new System.Drawing.Size(34, 24);
            this.write5.TabIndex = 25;
            this.write5.Text = "FF";
            this.write5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // read
            // 
            this.read.Controls.Add(this.label10);
            this.read.Controls.Add(this.Readvalueblock);
            this.read.Controls.Add(this.ReadDataBlock);
            this.read.Controls.Add(this.datat);
            this.read.Controls.Add(this.dataBox);
            this.read.Controls.Add(this.block_combo);
            this.read.Controls.Add(this.button3);
            this.read.Location = new System.Drawing.Point(21, 286);
            this.read.Name = "read";
            this.read.Size = new System.Drawing.Size(447, 144);
            this.read.TabIndex = 11;
            this.read.TabStop = false;
            this.read.Text = "Read";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(41, 61);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(51, 18);
            this.label10.TabIndex = 27;
            this.label10.Text = "Block";
            // 
            // Readvalueblock
            // 
            this.Readvalueblock.AutoSize = true;
            this.Readvalueblock.Location = new System.Drawing.Point(273, 11);
            this.Readvalueblock.Name = "Readvalueblock";
            this.Readvalueblock.Size = new System.Drawing.Size(169, 22);
            this.Readvalueblock.TabIndex = 26;
            this.Readvalueblock.Text = "Read a value block";
            this.Readvalueblock.UseVisualStyleBackColor = true;
            // 
            // ReadDataBlock
            // 
            this.ReadDataBlock.AutoSize = true;
            this.ReadDataBlock.Checked = true;
            this.ReadDataBlock.Location = new System.Drawing.Point(118, 11);
            this.ReadDataBlock.Name = "ReadDataBlock";
            this.ReadDataBlock.Size = new System.Drawing.Size(153, 22);
            this.ReadDataBlock.TabIndex = 25;
            this.ReadDataBlock.TabStop = true;
            this.ReadDataBlock.Text = "Read Data Block";
            this.ReadDataBlock.UseVisualStyleBackColor = true;
            // 
            // datat
            // 
            this.datat.AutoSize = true;
            this.datat.Location = new System.Drawing.Point(176, 91);
            this.datat.Name = "datat";
            this.datat.Size = new System.Drawing.Size(43, 18);
            this.datat.TabIndex = 23;
            this.datat.Text = "Data";
            // 
            // dataBox
            // 
            this.dataBox.Location = new System.Drawing.Point(6, 113);
            this.dataBox.Name = "dataBox";
            this.dataBox.ReadOnly = true;
            this.dataBox.Size = new System.Drawing.Size(435, 24);
            this.dataBox.TabIndex = 22;
            // 
            // block_combo
            // 
            this.block_combo.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3"});
            this.block_combo.Location = new System.Drawing.Point(112, 58);
            this.block_combo.Name = "block_combo";
            this.block_combo.Size = new System.Drawing.Size(33, 26);
            this.block_combo.TabIndex = 24;
            this.block_combo.Text = "0";
            // 
            // login
            // 
            this.login.Controls.Add(this.label7);
            this.login.Controls.Add(this.label6);
            this.login.Controls.Add(this.label5);
            this.login.Controls.Add(this.key6);
            this.login.Controls.Add(this.keyBox);
            this.login.Controls.Add(this.key5);
            this.login.Controls.Add(this.key4);
            this.login.Controls.Add(this.sectorBox);
            this.login.Controls.Add(this.button2);
            this.login.Controls.Add(this.key3);
            this.login.Controls.Add(this.key1);
            this.login.Controls.Add(this.key2);
            this.login.Location = new System.Drawing.Point(17, 92);
            this.login.Name = "login";
            this.login.Size = new System.Drawing.Size(451, 177);
            this.login.TabIndex = 10;
            this.login.TabStop = false;
            this.login.Text = "Login";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(9, 91);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(87, 18);
            this.label7.TabIndex = 20;
            this.label7.Text = "Key (HEX)";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(9, 58);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(77, 18);
            this.label6.TabIndex = 11;
            this.label6.Text = "Key Type";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(9, 26);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(58, 18);
            this.label5.TabIndex = 10;
            this.label5.Text = "Sector";
            // 
            // key6
            // 
            this.key6.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.key6.Location = new System.Drawing.Point(325, 89);
            this.key6.MaxLength = 2;
            this.key6.Name = "key6";
            this.key6.Size = new System.Drawing.Size(34, 24);
            this.key6.TabIndex = 17;
            this.key6.Text = "FF";
            this.key6.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // keyBox
            // 
            this.keyBox.FormattingEnabled = true;
            this.keyBox.Items.AddRange(new object[] {
            "KeyA",
            "KeyB"});
            this.keyBox.Location = new System.Drawing.Point(114, 55);
            this.keyBox.Name = "keyBox";
            this.keyBox.Size = new System.Drawing.Size(140, 26);
            this.keyBox.TabIndex = 9;
            this.keyBox.Text = "KeyA";
            // 
            // key5
            // 
            this.key5.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.key5.Location = new System.Drawing.Point(283, 89);
            this.key5.MaxLength = 2;
            this.key5.Name = "key5";
            this.key5.Size = new System.Drawing.Size(34, 24);
            this.key5.TabIndex = 16;
            this.key5.Text = "FF";
            this.key5.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // key4
            // 
            this.key4.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.key4.Location = new System.Drawing.Point(241, 89);
            this.key4.MaxLength = 2;
            this.key4.Name = "key4";
            this.key4.Size = new System.Drawing.Size(34, 24);
            this.key4.TabIndex = 15;
            this.key4.Text = "FF";
            this.key4.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // sectorBox
            // 
            this.sectorBox.Cursor = System.Windows.Forms.Cursors.Arrow;
            this.sectorBox.FormattingEnabled = true;
            this.sectorBox.Items.AddRange(new object[] {
            "00",
            "01",
            "02",
            "03",
            "04",
            "05",
            "06",
            "07",
            "08",
            "09",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15",
            "16",
            "17",
            "18",
            "19",
            "20"});
            this.sectorBox.Location = new System.Drawing.Point(114, 23);
            this.sectorBox.Name = "sectorBox";
            this.sectorBox.Size = new System.Drawing.Size(70, 26);
            this.sectorBox.TabIndex = 8;
            this.sectorBox.Text = "0";
            // 
            // key3
            // 
            this.key3.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.key3.Location = new System.Drawing.Point(199, 89);
            this.key3.MaxLength = 2;
            this.key3.Name = "key3";
            this.key3.Size = new System.Drawing.Size(34, 24);
            this.key3.TabIndex = 14;
            this.key3.Text = "FF";
            this.key3.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // key1
            // 
            this.key1.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.key1.Location = new System.Drawing.Point(115, 89);
            this.key1.MaxLength = 2;
            this.key1.Name = "key1";
            this.key1.Size = new System.Drawing.Size(34, 24);
            this.key1.TabIndex = 12;
            this.key1.Text = "FF";
            this.key1.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // key2
            // 
            this.key2.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.key2.Location = new System.Drawing.Point(157, 89);
            this.key2.MaxLength = 2;
            this.key2.Name = "key2";
            this.key2.Size = new System.Drawing.Size(34, 24);
            this.key2.TabIndex = 13;
            this.key2.Text = "FF";
            this.key2.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // select
            // 
            this.select.Controls.Add(this.groupBox2);
            this.select.Controls.Add(this.button1);
            this.select.Location = new System.Drawing.Point(17, 35);
            this.select.Name = "select";
            this.select.Size = new System.Drawing.Size(451, 51);
            this.select.TabIndex = 9;
            this.select.TabStop = false;
            this.select.Text = "Select Card";
            // 
            // groupBox2
            // 
            this.groupBox2.Location = new System.Drawing.Point(458, 6);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(518, 58);
            this.groupBox2.TabIndex = 12;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "groupBox2";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1155, 562);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.send_box);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.recive_box);
            this.Controls.Add(this.baud_list);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.list_port);
            this.Controls.Add(this.con_dis);
            this.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(222)));
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "ThaiEasyElec Mifare";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.groupBox1.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.write.ResumeLayout(false);
            this.write.PerformLayout();
            this.read.ResumeLayout(false);
            this.read.PerformLayout();
            this.login.ResumeLayout(false);
            this.login.PerformLayout();
            this.select.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button con_dis;
        private System.Windows.Forms.ComboBox list_port;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox baud_list;
        private System.IO.Ports.SerialPort serialPort;
        private System.Windows.Forms.TextBox recive_box;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox send_box;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox login;
        private System.Windows.Forms.GroupBox select;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox keyBox;
        private System.Windows.Forms.TextBox key1;
        private System.Windows.Forms.TextBox key2;
        private System.Windows.Forms.TextBox key4;
        private System.Windows.Forms.TextBox key3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox key6;
        private System.Windows.Forms.TextBox key5;
        private System.Windows.Forms.GroupBox read;
        private System.Windows.Forms.Label datat;
        private System.Windows.Forms.TextBox dataBox;
        private System.Windows.Forms.ComboBox block_combo;
        private System.Windows.Forms.GroupBox write;
        private System.Windows.Forms.Button bt_write;
        private System.Windows.Forms.TextBox write16;
        private System.Windows.Forms.TextBox write15;
        private System.Windows.Forms.TextBox write14;
        private System.Windows.Forms.TextBox write13;
        private System.Windows.Forms.TextBox write12;
        private System.Windows.Forms.TextBox write11;
        private System.Windows.Forms.TextBox write9;
        private System.Windows.Forms.TextBox write10;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox write4;
        private System.Windows.Forms.TextBox write8;
        private System.Windows.Forms.TextBox write2;
        private System.Windows.Forms.TextBox write7;
        private System.Windows.Forms.TextBox write1;
        private System.Windows.Forms.TextBox write6;
        private System.Windows.Forms.TextBox write3;
        private System.Windows.Forms.TextBox write5;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.ComboBox sectorBox;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox Block_write;
        private System.Windows.Forms.RadioButton ReadDataBlock;
        private System.Windows.Forms.RadioButton Readvalueblock;
        private System.Windows.Forms.RadioButton Writedatablock_radio;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.RadioButton Writevalueblock_radio;
        private System.Windows.Forms.RadioButton DECREMENTradio;
        private System.Windows.Forms.RadioButton INCREMENTradio;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button button6;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox n_key3;
        private System.Windows.Forms.TextBox n_key6;
        private System.Windows.Forms.TextBox n_key1;
        private System.Windows.Forms.TextBox n_key4;
        private System.Windows.Forms.TextBox n_key2;
        private System.Windows.Forms.TextBox n_key5;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button button7;
    }
}

