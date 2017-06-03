namespace EvalMathLab01
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea2 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend2 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.label26 = new System.Windows.Forms.Label();
            this.errorWindow4 = new System.Windows.Forms.TextBox();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.choosedFuncWindow = new System.Windows.Forms.TextBox();
            this.label24 = new System.Windows.Forms.Label();
            this.eilersChartsWindow = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.rightBorderWindow = new System.Windows.Forms.MaskedTextBox();
            this.startY = new System.Windows.Forms.MaskedTextBox();
            this.label31 = new System.Windows.Forms.Label();
            this.startX = new System.Windows.Forms.MaskedTextBox();
            this.label30 = new System.Windows.Forms.Label();
            this.label29 = new System.Windows.Forms.Label();
            this.label28 = new System.Windows.Forms.Label();
            this.firstDUFunc = new System.Windows.Forms.Button();
            this.evaluateButton4 = new System.Windows.Forms.Button();
            this.label25 = new System.Windows.Forms.Label();
            this.label23 = new System.Windows.Forms.Label();
            this.resultTable = new System.Windows.Forms.DataGridView();
            this.stepWindow = new System.Windows.Forms.MaskedTextBox();
            this.leftBorderWindow = new System.Windows.Forms.MaskedTextBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eilersChartsWindow)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.resultTable)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.SuspendLayout();
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.label26);
            this.tabPage4.Controls.Add(this.errorWindow4);
            this.tabPage4.Controls.Add(this.textBox7);
            this.tabPage4.Controls.Add(this.choosedFuncWindow);
            this.tabPage4.Controls.Add(this.label24);
            this.tabPage4.Controls.Add(this.eilersChartsWindow);
            this.tabPage4.Controls.Add(this.rightBorderWindow);
            this.tabPage4.Controls.Add(this.startY);
            this.tabPage4.Controls.Add(this.label31);
            this.tabPage4.Controls.Add(this.startX);
            this.tabPage4.Controls.Add(this.label30);
            this.tabPage4.Controls.Add(this.label29);
            this.tabPage4.Controls.Add(this.label28);
            this.tabPage4.Controls.Add(this.firstDUFunc);
            this.tabPage4.Controls.Add(this.evaluateButton4);
            this.tabPage4.Controls.Add(this.label25);
            this.tabPage4.Controls.Add(this.label23);
            this.tabPage4.Controls.Add(this.resultTable);
            this.tabPage4.Controls.Add(this.stepWindow);
            this.tabPage4.Controls.Add(this.leftBorderWindow);
            this.tabPage4.Location = new System.Drawing.Point(4, 22);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(754, 357);
            this.tabPage4.TabIndex = 3;
            this.tabPage4.Text = "Lab4 - Eiler\'s method";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // label26
            // 
            this.label26.AutoSize = true;
            this.label26.Location = new System.Drawing.Point(3, 304);
            this.label26.Name = "label26";
            this.label26.Size = new System.Drawing.Size(71, 13);
            this.label26.TabIndex = 26;
            this.label26.Text = "Error window:";
            // 
            // errorWindow4
            // 
            this.errorWindow4.Enabled = false;
            this.errorWindow4.Location = new System.Drawing.Point(3, 320);
            this.errorWindow4.Multiline = true;
            this.errorWindow4.Name = "errorWindow4";
            this.errorWindow4.Size = new System.Drawing.Size(257, 34);
            this.errorWindow4.TabIndex = 25;
            // 
            // textBox7
            // 
            this.textBox7.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.textBox7.Location = new System.Drawing.Point(97, 121);
            this.textBox7.Multiline = true;
            this.textBox7.Name = "textBox7";
            this.textBox7.Size = new System.Drawing.Size(59, 21);
            this.textBox7.TabIndex = 24;
            this.textBox7.Text = "Set (x0, y0):";
            // 
            // choosedFuncWindow
            // 
            this.choosedFuncWindow.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.choosedFuncWindow.Enabled = false;
            this.choosedFuncWindow.Location = new System.Drawing.Point(97, 19);
            this.choosedFuncWindow.Name = "choosedFuncWindow";
            this.choosedFuncWindow.Size = new System.Drawing.Size(163, 20);
            this.choosedFuncWindow.TabIndex = 12;
            // 
            // label24
            // 
            this.label24.AutoSize = true;
            this.label24.Location = new System.Drawing.Point(94, 78);
            this.label24.Name = "label24";
            this.label24.Size = new System.Drawing.Size(72, 13);
            this.label24.TabIndex = 6;
            this.label24.Text = "RightBorder =";
            // 
            // eilersChartsWindow
            // 
            chartArea2.Name = "ChartArea1";
            this.eilersChartsWindow.ChartAreas.Add(chartArea2);
            this.eilersChartsWindow.Cursor = System.Windows.Forms.Cursors.Cross;
            legend2.Name = "Legend2";
            legend2.Position.Auto = false;
            legend2.Position.Height = 30F;
            legend2.Position.Width = 30F;
            legend2.Position.X = 70F;
            this.eilersChartsWindow.Legends.Add(legend2);
            this.eilersChartsWindow.Location = new System.Drawing.Point(266, 3);
            this.eilersChartsWindow.Name = "eilersChartsWindow";
            this.eilersChartsWindow.Size = new System.Drawing.Size(485, 351);
            this.eilersChartsWindow.TabIndex = 4;
            this.eilersChartsWindow.Text = "chart2";
            // 
            // rightBorderWindow
            // 
            this.rightBorderWindow.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.rightBorderWindow.Location = new System.Drawing.Point(165, 78);
            this.rightBorderWindow.Mask = "#0.0000";
            this.rightBorderWindow.Name = "rightBorderWindow";
            this.rightBorderWindow.Size = new System.Drawing.Size(53, 13);
            this.rightBorderWindow.TabIndex = 1;
            this.rightBorderWindow.Text = "1";
            // 
            // startY
            // 
            this.startY.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.startY.Location = new System.Drawing.Point(224, 121);
            this.startY.Mask = "#.000";
            this.startY.Name = "startY";
            this.startY.Size = new System.Drawing.Size(36, 13);
            this.startY.TabIndex = 23;
            this.startY.Text = "1";
            // 
            // label31
            // 
            this.label31.AutoSize = true;
            this.label31.Location = new System.Drawing.Point(206, 121);
            this.label31.Name = "label31";
            this.label31.Size = new System.Drawing.Size(22, 13);
            this.label31.TabIndex = 22;
            this.label31.Text = ") = ";
            // 
            // startX
            // 
            this.startX.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.startX.Location = new System.Drawing.Point(172, 121);
            this.startX.Mask = "#.000";
            this.startX.Name = "startX";
            this.startX.Size = new System.Drawing.Size(35, 13);
            this.startX.TabIndex = 21;
            this.startX.Text = "0";
            // 
            // label30
            // 
            this.label30.AutoSize = true;
            this.label30.Location = new System.Drawing.Point(161, 121);
            this.label30.Name = "label30";
            this.label30.Size = new System.Drawing.Size(15, 13);
            this.label30.TabIndex = 20;
            this.label30.Text = "y(";
            // 
            // label29
            // 
            this.label29.AutoSize = true;
            this.label29.Location = new System.Drawing.Point(97, 3);
            this.label29.Name = "label29";
            this.label29.Size = new System.Drawing.Size(87, 13);
            this.label29.TabIndex = 19;
            this.label29.Text = "Chosen function:";
            // 
            // label28
            // 
            this.label28.AutoSize = true;
            this.label28.Location = new System.Drawing.Point(3, 3);
            this.label28.Name = "label28";
            this.label28.Size = new System.Drawing.Size(87, 13);
            this.label28.TabIndex = 18;
            this.label28.Text = "Choose function:";
            // 
            // firstDUFunc
            // 
            this.firstDUFunc.Location = new System.Drawing.Point(3, 19);
            this.firstDUFunc.Name = "firstDUFunc";
            this.firstDUFunc.Size = new System.Drawing.Size(87, 23);
            this.firstDUFunc.TabIndex = 14;
            this.firstDUFunc.Text = "y\' + 2y = (x ^ 2)";
            this.firstDUFunc.UseVisualStyleBackColor = true;
            this.firstDUFunc.Click += new System.EventHandler(this.firstDUFunc_Click);
            // 
            // evaluateButton4
            // 
            this.evaluateButton4.Location = new System.Drawing.Point(3, 50);
            this.evaluateButton4.Name = "evaluateButton4";
            this.evaluateButton4.Size = new System.Drawing.Size(87, 84);
            this.evaluateButton4.TabIndex = 10;
            this.evaluateButton4.Text = "Evaluate";
            this.evaluateButton4.UseVisualStyleBackColor = true;
            this.evaluateButton4.Click += new System.EventHandler(this.evaluateButton4_Click);
            // 
            // label25
            // 
            this.label25.AutoSize = true;
            this.label25.Location = new System.Drawing.Point(94, 50);
            this.label25.Name = "label25";
            this.label25.Size = new System.Drawing.Size(65, 13);
            this.label25.TabIndex = 7;
            this.label25.Text = "LeftBorder =";
            // 
            // label23
            // 
            this.label23.AutoSize = true;
            this.label23.Location = new System.Drawing.Point(95, 99);
            this.label23.Name = "label23";
            this.label23.Size = new System.Drawing.Size(38, 13);
            this.label23.TabIndex = 5;
            this.label23.Text = "Step =";
            // 
            // resultTable
            // 
            this.resultTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.resultTable.Location = new System.Drawing.Point(0, 148);
            this.resultTable.Name = "resultTable";
            this.resultTable.ReadOnly = true;
            this.resultTable.Size = new System.Drawing.Size(260, 153);
            this.resultTable.TabIndex = 3;
            // 
            // stepWindow
            // 
            this.stepWindow.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.stepWindow.Location = new System.Drawing.Point(134, 98);
            this.stepWindow.Mask = "00.00";
            this.stepWindow.Name = "stepWindow";
            this.stepWindow.Size = new System.Drawing.Size(42, 13);
            this.stepWindow.TabIndex = 2;
            this.stepWindow.Text = "001";
            // 
            // leftBorderWindow
            // 
            this.leftBorderWindow.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.leftBorderWindow.Location = new System.Drawing.Point(165, 50);
            this.leftBorderWindow.Mask = "#0.0000";
            this.leftBorderWindow.Name = "leftBorderWindow";
            this.leftBorderWindow.Size = new System.Drawing.Size(53, 13);
            this.leftBorderWindow.TabIndex = 0;
            this.leftBorderWindow.Text = "0";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Location = new System.Drawing.Point(12, 11);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(762, 383);
            this.tabControl1.TabIndex = 18;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(779, 401);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "EvalMathLabs";
            this.tabPage4.ResumeLayout(false);
            this.tabPage4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.eilersChartsWindow)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.resultTable)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Label label26;
        private System.Windows.Forms.TextBox errorWindow4;
        private System.Windows.Forms.TextBox textBox7;
        private System.Windows.Forms.TextBox choosedFuncWindow;
        private System.Windows.Forms.Label label24;
        private System.Windows.Forms.DataVisualization.Charting.Chart eilersChartsWindow;
        private System.Windows.Forms.MaskedTextBox rightBorderWindow;
        private System.Windows.Forms.MaskedTextBox startY;
        private System.Windows.Forms.Label label31;
        private System.Windows.Forms.MaskedTextBox startX;
        private System.Windows.Forms.Label label30;
        private System.Windows.Forms.Label label29;
        private System.Windows.Forms.Label label28;
        private System.Windows.Forms.Button firstDUFunc;
        private System.Windows.Forms.Button evaluateButton4;
        private System.Windows.Forms.Label label25;
        private System.Windows.Forms.DataGridView resultTable;
        private System.Windows.Forms.MaskedTextBox stepWindow;
        private System.Windows.Forms.MaskedTextBox leftBorderWindow;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.Label label23;
    }
}

