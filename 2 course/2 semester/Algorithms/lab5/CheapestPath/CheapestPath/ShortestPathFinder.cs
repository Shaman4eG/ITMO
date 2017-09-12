using Priority_Queue;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace CheapestPath
{
    class ShortestPathFinder
    {
        /// <summary>
        /// Cost of travel from start city to another city (index = city name).
        /// </summary>
        private float[] cost;

        /// <summary>
        /// Priority queue to extract shortest road to adjacent city.
        /// </summary>
        private SimplePriorityQueue<int, float> queue;

        /// <summary>
        /// List of visited cities. Adds a city if min cost of travel to it was already found.
        /// </summary>
        private List<int> visitedCities;

        public ShortestPathFinder(int numberOfCities)
        {
            cost = new float[numberOfCities + 1];
            queue = new SimplePriorityQueue<int, float>();
            visitedCities = new List<int>(numberOfCities + 1);
        }

        /// <summary>
        /// Finds shortest path using Dijkstra's algorithm.
        /// </summary>
        public void FindShortestPath(Input input)
        {
            ReadOnlyCollection <List<Road>> roads = input.ReadOnlyRoads;

            Initialization(input);

            // TODO: ADD ROAD CHANGING
            while (queue.Count != 0)
            {
                int fromCity = queue.Dequeue();

                foreach (Road road in roads[fromCity])
                {
                    // CHECK IT LOGICALLY
                    if (cost[fromCity] + road.CostOfTravel < cost[road.To])
                    {
                        //do stuff
                    }
                }
            }


        }

        /// <summary>
        /// Initializing costs array and queue.
        /// </summary>
        private void Initialization(Input input)
        {
            cost[input.StartCity] = 0;
            for (int city = 1; city <= input.NumberOfCities; city++)
            {
                if (city != input.StartCity) cost[city] = float.MaxValue;
                queue.Enqueue(city, cost[city]);
            }
        }
    }
}
