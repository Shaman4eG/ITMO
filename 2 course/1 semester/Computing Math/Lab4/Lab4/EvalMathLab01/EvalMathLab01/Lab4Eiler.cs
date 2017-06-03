using System;
using System.Collections.Generic;

namespace EvalMathLab01
{
    static class Lab4Eiler
    {
        public class Spot : IComparable
        {
            public double x = 0;
            public double y = 0;

            public Spot(double _x, double _y)
            {
                x = _x;
                y = _y;
            }

            public int CompareTo(object obj)
            {
                Spot other = obj as Spot;
                return this.x.CompareTo(other.x);
            }

        }

        static public List<Spot> EilersMethod(double step, double leftBorder, double rightBorder, double startX0, double startY0, Form1.DUFunction function)
        {
            List<Spot> resultTable = new List<Spot>();
            double y = startY0;
            double previousX = startX0;
            double previousY = startY0;
            resultTable.Add(new Spot(startX0, startY0));

            for (double x = (startX0 + step); x < rightBorder; x += step)
            {
                y = previousY + step * function(previousX, previousY);
                resultTable.Add(new Spot(x, y));
                previousY = y;
                previousX = x;
            }

            return resultTable;
        }
    }
}
