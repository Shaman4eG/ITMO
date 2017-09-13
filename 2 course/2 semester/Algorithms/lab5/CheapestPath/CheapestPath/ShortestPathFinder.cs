using System.Collections.Generic;
using System.Collections.ObjectModel;
using System;

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
        private List<ElementOfPriorityQueue> priorityQueue;

        /// <summary>
        /// List of visited cities. Adds a city if min cost of travel to it was already found.
        /// </summary>
        private List<ElementOfPath> parentCities;

        private class ElementOfPriorityQueue : IComparable<ElementOfPriorityQueue>
        {
            internal int VertexName { get; set; }
            internal float Cost { get; set; }

            internal ElementOfPriorityQueue(int vertexName, float cost)
            {
                VertexName = vertexName;
                Cost = cost;
            }

            public int CompareTo(ElementOfPriorityQueue other)
            {
                if (other == null) throw new NullReferenceException();

                return other.Cost.CompareTo(this.Cost);
            }
        }

        public ShortestPathFinder(int numberOfCities)
        {
            cost = new float[numberOfCities + 1];

            priorityQueue = new List<ElementOfPriorityQueue>(numberOfCities + 1);
            // Adding element to unused zero-indexed slot.
            priorityQueue.Add(new ElementOfPriorityQueue(0, float.MaxValue));

            parentCities = new List<ElementOfPath>(numberOfCities + 1);
            // Adding element to unused zero-indexed slot.
            parentCities.Add(new ElementOfPath());
        }



        /// <summary>
        /// Finds shortest path using Dijkstra's algorithm.
        /// </summary>
        /// <param name="input"> User-inputed data. </param>
        /// <returns> List of cities in shortest path. </returns>
        public void FindShortestPath(Input input, Output output)
        {
            ReadOnlyCollection< List<Road> > roads = input.ReadOnlyRoads;

            Initialization(input);
            DijkstraAlgorithm(roads, input.StartCity);
            output.cheapestTraveCost = cost[cost.Length - 1];
            output.SetShortestPath(FindPath());
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
                priorityQueue.Add(new ElementOfPriorityQueue(city, cost[city]));
                parentCities.Add(new ElementOfPath());
            }
        }

        private int FindIndexOfRoadToElement(int roadTo)
        {
            for (int i = 1; i < priorityQueue.Count; i++)
            {
                if (priorityQueue[i].VertexName == roadTo) return i;
            }

            return 0;
        }

        /// <summary>
        /// Finds shortest path in graph using Dijkstra's algorithm
        /// </summary>
        /// <param name="roads"> Edges of graph. </param>
        private void DijkstraAlgorithm(ReadOnlyCollection<List<Road>> roads, int startCity)
        {
           
            while (priorityQueue.Count > 0)
            {
                priorityQueue.Sort();
                int fromCity = priorityQueue[priorityQueue.Count - 1].VertexName;
                priorityQueue.RemoveAt(priorityQueue.Count - 1);

                foreach (Road road in roads[fromCity])
                {
                    float costOfTravelWithInsurance = road.CostOfTravel;
                    bool roadChanged = RoadTypeChanged(road, startCity);
                    if (roadChanged) costOfTravelWithInsurance *= Constants.insuranceCoefficient;
                    if (cost[fromCity] + costOfTravelWithInsurance < cost[road.To])
                    {
                        int indexOfRoadToElement = FindIndexOfRoadToElement(road.To);
                        cost[road.To] = cost[fromCity] + costOfTravelWithInsurance;
                        priorityQueue[indexOfRoadToElement].Cost = cost[road.To];
                        ElementOfPath newCity = new ElementOfPath { ParentCity = fromCity, CameOnSuchRoad = road.RoadType };
                        parentCities[road.To] = newCity;
                    }
                }
            }
        }

        private bool RoadTypeChanged(Road road, int startCity)
        {
            if (road.From == startCity) return true;
            if (road.RoadType != parentCities[road.From].CameOnSuchRoad) return true;
            else return false;
        }

        /// <summary>
        /// Returns cities of shortest path.
        /// </summary>
        private List<ElementOfPath> FindPath()
        {
            int parentCity = parentCities[parentCities.Count - 1].ParentCity;
            List<ElementOfPath> citiesInPath = new List<ElementOfPath>();
            // Adding last city, which is the same as last index of parentCities.
            citiesInPath.Add(parentCities[parentCities.Count - 1]);

            while (parentCity != 1)
            {
                citiesInPath.Add(parentCities[parentCity]);
                parentCity = parentCities[parentCity].ParentCity;
            }

            citiesInPath.Reverse();

            return citiesInPath;
        }
    }
}
