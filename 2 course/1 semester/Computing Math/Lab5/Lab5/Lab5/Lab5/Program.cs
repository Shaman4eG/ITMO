using System;

namespace Lab5
{
    class Lab5
    {
        static void Main(string[] args)
        {
            double af0 = 0, af1 = 0, bt0 = 0, bt1 = 0, h = 0, A = 0, B = 0, x0 = 0, xn = 0;
            double pi = 0, qi = 0, fi = 0;
            int i, n;
            bool qiMultiply = false, qiDivide = false;

            while (true)
            {
                Console.Clear();

                // Processing user's choice.
                Console.WriteLine("Choose function:\n1) y'' + xy' - 0.5 * y / x = 1\nBorders:\n    y(2) + 2y'(2) = 1\n    y(2.3) = 2.15\n\n2)  y'' - 2xy' - 2y = -4\nBorders:\n    y(0) - y'(0) = 0\n    y(1) = 1 + e\n\n3) Exit\n");
                int chooser = 0;

                bool wrongInput = true;
                do
                {
                    if (Int32.TryParse(Console.ReadLine(), out chooser))
                    {
                        switch (chooser)
                        {
                            case 1:
                                A = 1; B = 2.15;
                                af0 = 1; af1 = 2;
                                bt0 = 1; bt1 = 0;
                                h = 0.05;
                                x0 = 2; xn = 2.3;
                                pi = 1; qi = -0.5;
                                fi = 1;
                                qiDivide = true;
                                wrongInput = false;
                                break;

                            case 2:
                                A = 0; B = 3.718;
                                af0 = 1; af1 = -1;
                                bt0 = 1; bt1 = 0;
                                h = 0.1;
                                x0 = 0; xn = 1;
                                pi = -2; qi = -2;
                                fi = -4;
                                qiMultiply = true;
                                wrongInput = false;
                                break;

                            case 3:
                                Environment.Exit(0);
                                break;

                            default:
                                Console.WriteLine("Invalid input.");
                                break;
                        }
                    }
                    else Console.WriteLine("Invalid input.");

                } while (wrongInput);

                // Computing.
                n = (int)Math.Round((xn - x0) / h);
                var compMethod = new ComputingMethod();
                double[,] result = new double[n + 1, 2];
                result = compMethod.Progonka(A, B, af0, af1, bt0, bt1, h, x0, xn, n, pi, qi, qiMultiply, qiDivide, fi);


                // Output
                for (i = 0; i <= n; i++)
                    Console.WriteLine("x = {0:F3}, y = {1:F4}", result[i, 0], result[i, 1]);
                Console.ReadKey();
            }
        }
    }

    class ComputingMethod
    {
        double[] c = new double[100];
        double[] d = new double[100];
        double[] F = new double[100];
        double[] k = new double[100];
        double[] m = new double[100];
        double[] p = new double[100];
        double[] q = new double[100];
        double[] y = new double[100];
        double[] x = new double[100];

        public double[,] Progonka(double A, double B, double af0, double af1, double bt0, double bt1, double h, double x0, double xn, int n, double pi, double qi, bool qiMultiply, bool qiDivide, double fi)
        {
            // Computing coefficients of equasion.
            for (int i = 0; i <= n; i++)
            {
                x[i] = x0 + i * h;
                p[i] = pi * x[i];
                if (qiMultiply) q[i] = qi * x[i];
                else q[i] = qi / x[i];
                F[i] = fi;
            }

            // Computing coefficients, using forward algorithm.
            c[0] = af1 / (af0 * h - af1);
            d[0] = (A * h) / af1;
            for (int i = 1; i < n; i++)
            {
                m[i] = (2 * h * h * q[i] - 4) / (2 + h * p[i]);
                k[i] = (2 - h * p[i]) / (2 + h * p[i]);
                F[i] = 2 * F[i] / (2 + h * p[i]);
                d[i] = F[i] * h * h - k[i] * c[i - 1] * d[i - 1];
                c[i] = 1 / (m[i] - k[i] * c[i - 1]);
            }

            // Computing yi, using backward algorithm.
            y[n] = (B * h + bt1 * c[n - 1] * d[n - 1]) / (bt0 * h + bt1 * (c[n - 1] + 1));
            for (int i = n - 1; i >= 0; i--)
                y[i] = c[i] * (d[i] - y[i + 1]);

            // Preparting result.
            double[,] result = new double[n + 1, 2];
            for (int i = 0; i <= n; i++)
            {
                result[i, 0] = x[i];
                result[i, 1] = y[i];
            }

            return result;
        }
    }
}

