using System.IO;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace CheapestPath
{
    class Input
    {
        /// <summary>
        /// User-set number of cities.
        /// </summary>
        internal int NumberOfCities
        {
            get { return NumberOfCities; }
            set
            {
                if ((value >= Constants.minNumberOfCities) &&
                    (value <= Constants.maxNumberOfCities))
                {
                    NumberOfCities = value;
                }
            }
        }

        /// <summary>
        /// User-set number of roads. 
        /// </summary>
        internal int NumberOfRoads
        {
            get { return NumberOfRoads; }
            set
            {
                if ((value >= Constants.minNumberOfRoads) &&
                    (value <= Constants.maxNumberOfRoads))
                {
                    NumberOfRoads = value;
                }
            }
        }

        /// <summary>
        /// User-set start city.
        /// Sets only if: 
        /// 1) city number is in list of possible city numbers; 
        /// 2) is not the same as finish city.
        /// </summary>
        internal int StartCity
        {
            get { return StartCity; }
            set
            {
                if ((value >= Constants.minCityNumber) ||
                    (value <= Constants.maxCityNumber))
                {
                    if (value != FinishCity)
                    {
                        StartCity = value;
                    }
                }
            }
        }

        /// <summary>
        /// User-set finish city.
        /// Sets only if: 
        /// 1) city number is in list of possible city numbers; 
        /// 2) is not the same as start city.
        /// </summary>
        internal int FinishCity
        {
            get { return FinishCity; }
            set
            {
                if ((value >= Constants.minCityNumber) ||
                    (value <= Constants.maxCityNumber))
                {
                    if (value != StartCity)
                    {
                        FinishCity = value;
                    }
                }
            }
        }

        /// <summary>
        /// Keeps roads (edges) of transport system.
        /// </summary>
        private List<Road> roads;

        internal void GetData(string fileName)
        {
            string[] inputData = File.ReadAllLines(fileName);

            
        }
    }
}
