using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;
using System.Drawing;
using System.Diagnostics;
using static EvalMathLab01.Lab3Lagr;
using System.Windows.Forms.DataVisualization.Charting;

namespace EvalMathLab01
{
    public partial class Form1 : Form
    {
        public delegate double Function(double a);
        Function Func;

        public Form1()
        {
            InitializeComponent();
            chart1.ChartAreas[0].CursorX.IsUserSelectionEnabled = true;
            chart1.ChartAreas[0].CursorY.IsUserSelectionEnabled = true;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }


        int numberOfInput = default(int);
        double[,] inputTable;
        double leftBorder;
        double rightBorder;
        double dx;

        private void evaluate3_Click(object sender, EventArgs e)
        {
            errorWindow3.Clear();
            int size = (int)(Math.Abs(rightBorder - leftBorder));
            if ((textBox5.Text != "") && (maskedTextBox7.Text != "") && (maskedTextBox8.Text != "") && (maskedTextBox9.Text != "") && (numberOfInput != default(int)))
            {
                try
                {
                    leftBorder = Convert.ToDouble(maskedTextBox7.Text);
                    rightBorder = Convert.ToDouble(maskedTextBox8.Text);

                    if (leftBorder >= rightBorder)
                    {
                        errorWindow3.AppendText("Right border is smaller than left border.\n");
                        return;
                    }

                    dx = Convert.ToDouble(maskedTextBox9.Text);
                    if (dx < 0.00001)
                    {
                        errorWindow3.AppendText("Accuracy can't equal 0.\n");
                        return;
                    }
                }
                catch (FormatException)
                {
                    errorWindow3.AppendText("Wrong number entered in borders or accuracy field.\n");
                    return;
                }
                inputTable = new double[2, numberOfInput];
                if (leftBorder < rightBorder)
                {
                    chart1.ChartAreas[0].AxisX.Minimum = leftBorder;
                    chart1.ChartAreas[0].AxisY.Minimum = leftBorder;
                    chart1.ChartAreas[0].AxisX.Maximum = rightBorder;
                    chart1.ChartAreas[0].AxisY.Maximum = rightBorder;
                }
                else
                {
                    chart1.ChartAreas[0].AxisX.Minimum = leftBorder;
                    chart1.ChartAreas[0].AxisY.Minimum = leftBorder;
                    chart1.ChartAreas[0].AxisX.Maximum = rightBorder;
                    chart1.ChartAreas[0].AxisY.Maximum = rightBorder;
                }
                for (int i = 0; i < numberOfInput; i++)
                {
                    inputTable[0, i] = Convert.ToDouble(dataGridView2.Rows[0].Cells[i].Value);
                    inputTable[1, i] = Convert.ToDouble(dataGridView2.Rows[1].Cells[i].Value);
                }
            }
            else
            {
                errorWindow3.AppendText("Not all fields are filled.\n");
                return;
            }

            DrawFirstFunction();
            DrawSecondFunction();
            DrawThirdFunction(chart1, inputTable, 2, errorWindow3, leftBorder, rightBorder, dx, numberOfInput);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            errorWindow3.Clear();
            try
            {
                numberOfInput = Convert.ToInt32(maskedTextBox6.Text);
            }
            catch (FormatException)
            {
                errorWindow3.AppendText("Wrong numer of input points entered.\n");
                return;
            }

            dataGridView2.ColumnCount = numberOfInput;
            dataGridView2.RowCount = 2;
            dataGridView2.Rows[0].HeaderCell.Value = "x";
            dataGridView2.Rows[1].HeaderCell.Value = "y";

            for (int i = 0; i < numberOfInput; i++)
            {
                dataGridView2.Columns[i].HeaderCell.Value = Convert.ToString(i + 1);
            }
        }

        private void DrawFirstFunction()
        {
            chart1.Series.Clear();
            try
            {
                chart1.Series.Add("Function 1: " + textBox5.Text);
                chart1.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            }
            catch (ArgumentException)
            {

            }
            for (double i = leftBorder; i <= rightBorder; i += dx)
            {
                chart1.Series[0].Points.AddXY(i, Func(i));
            }
        }

        private void DrawSecondFunction()
        {
            try
            {
                chart1.Series.Add("Function 2: User's points");
                chart1.Series[1].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Point;
                for (int i = 0; i < numberOfInput; i++)
                {
                    double x = Convert.ToDouble(dataGridView2.Rows[0].Cells[i].Value);
                    double y = Convert.ToDouble(dataGridView2.Rows[1].Cells[i].Value);
                    chart1.Series[1].Points.AddXY(x, y);
                }
            }
            catch (ArgumentException)
            {
                errorWindow3.AppendText("Error catched!\n");
            }
        }

        private void DrawThirdFunction(Chart chart, double[,] input, int series, TextBox errorWindow, double leftBorder, double rightBorder, double dx, int numberOfInput)
        {
            List<Spot> result = new List<Spot>();
            try
            {
                chart.Series.Add("Function 3: Interpolated function");
                chart.Series[series].ChartType = SeriesChartType.Spline;
                result = Lab3Lagr.Evaluate(leftBorder, rightBorder, input, numberOfInput, dx);
                for (int i = 0; i < result.Count; i++)
                {
                    chart.Series[series].Points.AddXY(result[i].x, result[i].y);
                }
            }
            catch (ArgumentException)
            {
                errorWindow.AppendText("Error catched!\n");
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            errorWindow3.Clear();
            try
            {
                dx = Convert.ToDouble(maskedTextBox9.Text);
                if (dx < 0.00001)
                {
                    errorWindow3.AppendText("Accuracy can't equal 0.\n");
                    return;
                }
            }
            catch (FormatException)
            {
                errorWindow3.AppendText("Accuracy window is null.\n");
                return;
            }

            if (checkBox1.Checked)
            {
                dataGridView2.Enabled = true;
                dataGridView2.EditMode = DataGridViewEditMode.EditOnEnter;
            }
            else
            {
                if ((Func != null) && (textBox5.Text != ""))
                {
                    dataGridView2.Enabled = false;
                    for (int i = 0; i < numberOfInput; i++)
                    {
                        try
                        {
                            dataGridView2.Rows[1].Cells[i].Value = Func(Convert.ToDouble(dataGridView2.Rows[0].Cells[i].Value));
                        }
                        catch (FormatException)
                        {
                            errorWindow3.AppendText("Wrong symbol in input table column number " +
                                +i + ": x =" + dataGridView2.Rows[0].Cells[i].Value + "\n");
                        }
                    }
                }
                else
                {
                    errorWindow3.AppendText("No function choosed.\n");
                    checkBox1.Checked = true;
                    return;
                }

            }
        }

        private void func1_Click(object sender, EventArgs e)
        {
            Func = x => Math.Sin(x);
            textBox5.Text = "sin(x)";
        }

        private void func2_Click(object sender, EventArgs e)
        {
            textBox5.Text = "x^3";
            Func = x => x * x * x;
        }

        private void func3_Click(object sender, EventArgs e)
        {
            Func = x => Math.Sqrt(x);
            textBox5.Text = "sqrt(x)";
        }

    }
}