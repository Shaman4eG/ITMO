using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.IO;
using System.Drawing;
using System.Diagnostics;
using static EvalMathLab01.Lab4Eiler;
using System.Windows.Forms.DataVisualization.Charting;

namespace EvalMathLab01
{
    public partial class Form1 : Form
    {
        public delegate double Function(double a);

        public Form1()
        {
            InitializeComponent();

            eilersChartsWindow.ChartAreas[0].CursorX.IsUserSelectionEnabled = true;
            eilersChartsWindow.ChartAreas[0].CursorY.IsUserSelectionEnabled = true;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }


        public delegate double DUFunction(double x, double y);
        DUFunction function;

        private void evaluateButton4_Click(object sender, EventArgs e)
        {
            errorWindow4.Clear();
            double step;
            double leftBorder;
            double rightBorder;
            double startX0;
            double startY0;

            if(choosedFuncWindow.Text == "")
            {
                errorWindow4.AppendText("Function isn't choosed./n");
                return;
            }

            try
            {
                leftBorder = Convert.ToDouble(leftBorderWindow.Text);
                if (leftBorder > 10)
                {
                    errorWindow4.AppendText("Left border has maximum value of 10.");
                    return;
                }
            }
            catch(FormatException)
            {
                errorWindow4.AppendText("Left border isn't set./n");
                return;
            }

            try
            {
                rightBorder = Convert.ToDouble(rightBorderWindow.Text);
                if (rightBorder > 10)
                {
                    errorWindow4.AppendText("Right border has maximum value of 10.");
                    return;
                }
            }
            catch (FormatException)
            {
                errorWindow4.AppendText("Right border isn't set./n");
                return;
            }

            try
            {
                step = Convert.ToDouble(stepWindow.Text);
                if (step < 0.05)
                {
                    errorWindow4.AppendText("Step has minimum value of 0.05");
                    return;
                }
            }
            catch (FormatException)
            {
                errorWindow4.AppendText("Accuracy isn't set./n");
                return;
            }

            try
            {
                startX0 = Convert.ToDouble(startX.Text);
            }
            catch (FormatException)
            {
                errorWindow4.AppendText("Start x0 isn't set./n");
                return;
            }

            try
            {
                startY0 = Convert.ToDouble(startY.Text);
            }
            catch (FormatException)
            {
                errorWindow4.AppendText("Start y0 isn't set./n");
                return;
            }

            if (leftBorder > rightBorder)
            {
                double r = rightBorder;
                rightBorder = leftBorder;
                leftBorder = r;
            }

            

            List<Spot> eilerResult = EilersMethod(step, leftBorder, rightBorder, startX0, startY0, function);

            double[,] convertedResult = new double[2, eilerResult.Count];

            for(int i = 0; i < eilerResult.Count; i++)
            {
                convertedResult[0, i] = eilerResult[i].x;
                convertedResult[1, i] = eilerResult[i].y; 
            }
            eilersChartsWindow.Series.Clear();

            List<Spot> result = Lab3Lagr.Evaluate(leftBorder, rightBorder, convertedResult, eilerResult.Count, step);

            double min = double.MaxValue;
            double max = double.MinValue;

            for(int i = 0; i < result.Count; i++)
            {
                if((result[i].x == startX0) && (result[i].y != startY0))
                {
                    result[i].y = startY0;
                }

                if((!result[i].y.Equals(Double.NaN)) && (!result[i].y.Equals(Double.NegativeInfinity)) && (!result[i].y.Equals(Double.PositiveInfinity)))
                {
                    if (max < result[i].y)
                    {
                        max = result[i].y;
                        continue;
                    }

                    if (min > result[i].y)
                    {
                        min = result[i].y;
                        continue;
                    }
                }

            }

            if(min.Equals(double.MaxValue))
            {
                errorWindow4.AppendText("Approximate error(All y's is Not A number!).");
                return;
            }


            eilersChartsWindow.ChartAreas[0].AxisX.Minimum = result[0].x;
            eilersChartsWindow.ChartAreas[0].AxisY.Minimum = min - 3;
            eilersChartsWindow.ChartAreas[0].AxisX.Maximum = result[result.Count - 1].x;
            eilersChartsWindow.ChartAreas[0].AxisY.Maximum = max + 3;

            resultTable.RowCount = eilerResult.Count;
            resultTable.ColumnCount = 2;

            resultTable.Columns[0].HeaderCell.Value = "x";
            resultTable.Columns[1].HeaderCell.Value = "y";

            try
            {
                eilersChartsWindow.Series.Add("Function 1: Eilers Method");
                eilersChartsWindow.Series[0].ChartType = SeriesChartType.Spline;
                

                for (int i = 0; i < result.Count; i++)
                {
                    if((result[i].x <= result[result.Count - 1].x) && (result[i].x >= result[0].x) && (result[i].y <= max) && (result[i].y >= min))
                    {
                        eilersChartsWindow.Series[0].Points.AddXY(Convert.ToSingle(result[i].x), Convert.ToSingle(result[i].y));
                    }
                }
            }
            catch (ArgumentException)
            {
                errorWindow4.AppendText("Error catched!\n");
            }



            for (int i = 0; i < eilerResult.Count; i++)
            {
                resultTable.Rows[i].HeaderCell.Value = Convert.ToString(i + 1);
                resultTable.Rows[i].Cells[0].Value = Convert.ToString(Convert.ToSingle(eilerResult[i].x));
                resultTable.Rows[i].Cells[1].Value = Convert.ToString(Convert.ToSingle(eilerResult[i].y));
            }
        }



        private void firstDUFunc_Click(object sender, EventArgs e)
        {
            choosedFuncWindow.Text = "y' + 2y = (x ^ 2)";
            function = (x, y) => (x * x - 2 * y);
        }

    }
}