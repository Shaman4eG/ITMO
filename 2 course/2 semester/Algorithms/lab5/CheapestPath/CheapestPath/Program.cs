﻿using System;

namespace CheapestPath
{
    class Program
    {
        static void Main(string[] args)
        {
            var input = new Input();
            input.GetData();

            var pathFinder = new ShortestPathFinder(input.NumberOfCities);
            var output = new Output();
            pathFinder.FindShortestPath(input, output);

            output.OutputData(input.FinishCity);

            Console.WriteLine("\nPress any key to continue...");
            Console.ReadKey();
        }
    }
}
