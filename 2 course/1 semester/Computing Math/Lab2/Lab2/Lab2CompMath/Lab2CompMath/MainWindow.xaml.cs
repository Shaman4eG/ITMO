using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Lab2CompMath
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        public delegate double Function(double x);
        Function function;

        public static double X(double x)
        {
            return x;
        }

        private void Solve_Click(object sender, RoutedEventArgs e)
        {
            double accuracy = 0;
            double lowerLimit = 0;
            double upperLimit = 0;

            // Checking input.
            var inputChecker = new CheckerOfInput();
            if (!inputChecker.CheckAccuracy(Accuracy.Text, out accuracy)) return;
            if (!inputChecker.CheckRangeOfIntegration(LowerLimit.Text, out lowerLimit)) return;
            if (!inputChecker.CheckRangeOfIntegration(UpperLimit.Text, out upperLimit)) return;

            // Changed to -1, if lower limit >= upper limit.
            int signOfResult = 1;

            // Changing sign, if lower limit >= upper limit.
            if (lowerLimit >= upperLimit)
            {
                signOfResult = -1;

                // Swapping limits.
                double tmp = lowerLimit;
                lowerLimit = upperLimit;
                upperLimit = tmp;
            }

            // Preparing data.
            GetCurrentFunction();


            long numberOfSeparations = 0;
            double delta = 0.0;

            // Checking input method and computing.
            var compMethod = new RectanglesComputingMethods();
            if (LeftRectangles.IsChecked == true)
            {
                Result.Text = (signOfResult * compMethod.ComputeUsingLeftRectangles(function, lowerLimit, upperLimit, accuracy, out numberOfSeparations, out delta)).ToString();
            }
            else if (RightRectangles.IsChecked == true)
            {
                Result.Text = (signOfResult * compMethod.ComputeUsingRightRectangles(function, lowerLimit, upperLimit, accuracy, out numberOfSeparations, out delta)).ToString();
            }
            else if (MiddleRectangles.IsChecked == true)
            {
                Result.Text = (signOfResult * compMethod.ComputeUsingMiddleRectangles(function, lowerLimit, upperLimit, accuracy, out numberOfSeparations, out delta)).ToString();
            }

            // Output.
            NumberOfPartitions.Text = numberOfSeparations.ToString();
            Error.Text = delta.ToString();
    }



        private class CheckerOfInput
        {
            internal bool CheckAccuracy(string stringAccuracy, out double doubleAccuracy)
            {
                doubleAccuracy = 0;
                if (!Regex.IsMatch(stringAccuracy, @"^\d{1,3},\d{1,6}$|^[1-9]{1,8}$")) // НОЛИК ВЗРЫВАЕТ, УБЕРИ
                {
                    MessageBox.Show("Неверный ввод точности.", "Ошибка ввода", MessageBoxButton.OK, MessageBoxImage.Error);
                    return false;
                }

                doubleAccuracy = Convert.ToDouble(stringAccuracy);
                return true;
            }

            internal bool CheckRangeOfIntegration(string stringLimit, out double doubleLimit)
            {
                doubleLimit = 0;
                if (!Regex.IsMatch(stringLimit, @"^-?[0-5]{1}[0-9]?,\d{1,6}$|^-?[1-5]{1}\d{0,1}$|^0$"))
                {
                    MessageBox.Show("Неверный ввод предела интегрирования.", "Ошибка ввода", MessageBoxButton.OK, MessageBoxImage.Error);
                    return false;
                }

                doubleLimit = Convert.ToDouble(stringLimit);
                return true;
            }
        }

        internal void GetCurrentFunction()
        {
            if (xFunc.IsChecked == true) function = X;
            else if (sinFunc.IsChecked == true) function = Math.Sin;
            else if (conFunc.IsChecked == true) function = Math.Cos;
        }

        internal class RectanglesComputingMethods
        {
            public double ComputeUsingLeftRectangles(Function func, double a, double b, double accur, out long numOfPartitions, out double delta)
            {
                double I1 = 0, I2;
                double x;
                double s, h, sigma = (1.0 / 3);

                int n = 10;

                double diff;

                do
                {
                    h = (b - a) / n;
                    x = a;
                    s = 0;

                    for (long i = 0; i < n; i++)
                    {
                        s = s + func(x);
                        x += h;
                    }
                    I2 = s * h;

                    diff = sigma * Math.Abs(I2 - I1); 

                    if (diff > accur)
                    {
                        n = n * 2;
                        I1 = I2;
                    }

                } while (diff > accur);

                numOfPartitions = n;
                delta = Math.Abs(I2 - I1);
                return I2;
            }

            public double ComputeUsingRightRectangles(Function func, double a, double b, double accur, out long numOfPartitions, out double delta)
            {
                double I1 = 0, I2;
                double x1;
                double s, h, sigma = (1.0 / 3);

                int n = 10;

                double diff;
                do
                {
                    h = (b - a) / n;
                    x1 = a;
                    s = 0;

                    for (int i = 0; i < n; i++)
                    {
                        s = s + func(x1 + h);
                        x1 += h;
                    }
                    I2 = s * h;

                    diff = sigma * Math.Abs(I2 - I1);

                    if (diff > accur)
                    {
                        n = n * 2;
                        I1 = I2;
                    }


                } while (diff > accur);

                numOfPartitions = n;
                delta = Math.Abs(I2 - I1);
                return I2;
            }

            public double ComputeUsingMiddleRectangles(Function func, double a, double b, double accur, out long numOfPartitions, out double delta)
            {
                double I1 = 0, I2;
                double x1;
                double s, h, sigma = (1.0 / 3);

                int n = 10;

                double diff;
                do
                {
                    h = (b - a) / n;
                    x1 = a;
                    s = 0;

                    for (int i = 0; i < n; i++)
                    {
                        s = s + func((x1 + x1 + h) / 2);
                        x1 += h;
                    }
                    I2 = s * h;

                    diff = sigma * Math.Abs(I2 - I1);

                    if (diff > accur)
                    {
                        n = n * 2;
                        I1 = I2;
                    }


                } while (diff > accur);

                numOfPartitions = n;
                delta = Math.Abs(I2 - I1);
                return I2;
            }
        }



    }
}
