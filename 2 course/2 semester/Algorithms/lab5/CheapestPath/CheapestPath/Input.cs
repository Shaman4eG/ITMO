using System.IO;
using System.Collections.Generic;
using System;


namespace CheapestPath
{
    class Input
    {
        /// <summary>
        /// Calculated based on number of cities. 
        /// Minimum number of roads = number of cities - 1
        /// </summary>
        internal int MinNumberOfRoads { get; private set; }

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
                if ((value >= minNumberOfRoads) &&
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

            bool gotNumberOfCitiesSuccessfully = ProcessResultsOfGettingNumberOfRoads(inputData[0]);
            if (!gotNumberOfCitiesSuccessfully) return;

            MinNumberOfRoads = NumberOfCities - 1;



        }

        // SECTION START: get number of cities.
        /// <summary>
        /// Calls function to get number of cities and works with result.
        /// </summary>
        /// <param name="numberOfCities"> Inputed string keeping number of cities. </param>
        /// <returns>  
        /// Success: number of city is valid, returns true.
        /// Failure: invalid number of cities, error message is shown, returns false;
        /// </returns>
        private bool ProcessResultsOfGettingNumberOfCities(string numberOfCities)
        {
            NumberOfCities = GetNumberOfCities(numberOfCities);

            if (NumberOfCities != 0) return true;
            else
            {
                NumberOfCitiesErrorMessage();
                return false;
            }
        }

        /// <summary>
        /// Checks that inputed number of cities is an int value and is within set range.
        /// </summary>
        /// <param name="numberOfCities"> Inputed string keeping number of cities. </param>
        /// <returns> 
        /// Success: returns number of cities int value.
        /// Failure: returns 0.
        /// </returns>
        private int GetNumberOfCities(string numberOfCities)
        {
            int numberOfCitiesKeeper;
            if (int.TryParse(numberOfCities, out numberOfCitiesKeeper))
            {
                if ((numberOfCitiesKeeper >= Constants.minNumberOfCities) &&
                    (numberOfCitiesKeeper <= Constants.maxNumberOfCities))
                {
                    NumberOfCities = numberOfCitiesKeeper;
                }
            }

            return 0;
        }

        /// <summary>
        /// Outputs to console message about invalid number of cities input.
        /// </summary>
        private void NumberOfCitiesErrorMessage()
        {
            Console.WriteLine($"Invalid number of cities. Should be within range " +
                  $"[{Constants.minNumberOfCities}; " +
                  $"{Constants.maxNumberOfCities}]");
        }
        // SECTION END

        // SECTION START: get number of roads.
        /// <summary>
        /// Calls function to get number of roads and works with result.
        /// </summary>
        /// <param name="numberOfCities"> Inputed string keeping number of roads. </param>
        /// <returns>  
        /// Success: number of roads is valid, returns true.
        /// Failure: invalid number of roads, error message is shown, returns false;
        /// </returns>
        private bool ProcessResultsOfGettingNumberOfRoads(string numberOfRoads)
        {
            NumberOfRoads = GetNumberOfRoads(numberOfRoads);

            if (NumberOfRoads != 0) return true;
            else
            {
                NumberOfRoadsErrorMessage();
                return false;
            }
        }

        /// <summary>
        /// Checks that inputed number of roads is an int value and is within set range.
        /// </summary>
        /// <param name="numberOfCities"> Inputed string keeping number of roads. </param>
        /// <returns> 
        /// Success: returns number of roads int value.
        /// Failure: returns 0.
        /// </returns>
        private int GetNumberOfRoads(string numberOfRoads)
        {
            int numberOfRoadsKeeper;
            if (int.TryParse(numberOfRoads, out numberOfRoadsKeeper))
            {
                if ((numberOfRoadsKeeper >= MinNumberOfRoads) &&
                    (numberOfRoadsKeeper <= Constants.maxNumberOfRoads))
                {
                    return numberOfRoadsKeeper;
                }
            }

            return 0;
        }

        /// <summary>
        /// Outputs to console message about invalid number of roads input.
        /// </summary>
        private void NumberOfRoadsErrorMessage()
        {
            Console.WriteLine($"Invalid number of roads. Should be within range " +
                  $"[{MinNumberOfRoads}; " +
                  $"{Constants.maxNumberOfRoads}]");
        }
        // SECTION END
    }
}
