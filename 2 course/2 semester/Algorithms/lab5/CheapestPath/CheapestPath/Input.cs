using System.IO;
using System.Collections.Generic;
using System;
using System.Collections.ObjectModel;

namespace CheapestPath
{
    /// <summary>
    /// Processes and keeps input data from txt file.
    /// </summary>
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
            get { return numberOfCities; }
            set
            {
                if ((value >= Constants.minNumberOfCities) &&
                    (value <= Constants.maxNumberOfCities))
                {
                    numberOfCities = value;
                }
            }
        }
        private int numberOfCities = 0;

        /// <summary>
        /// User-set number of roads. 
        /// </summary>
        internal int NumberOfRoads
        {
            get { return numberOfRoads; }
            set
            {
                if ((value >= MinNumberOfRoads) &&
                    (value <= Constants.maxNumberOfRoads))
                {
                    numberOfRoads = value;
                }
            }
        }
        private int numberOfRoads = 0;

        /// <summary>
        /// User-set start city.
        /// Sets only if: 
        /// 1) city number is in list of possible city numbers; 
        /// 2) is not the same as finish city.
        /// </summary>
        internal int StartCity
        {
            get { return startCity; }
            set
            {
                if ((value >= Constants.minCityNumber) ||
                    (value <= Constants.maxCityNumber))
                {
                    if (value != FinishCity)
                    {
                        startCity = value;
                    }
                }
            }
        }
        private int startCity = 0;

        /// <summary>
        /// User-set finish city.
        /// Sets only if: 
        /// 1) city number is in list of possible city numbers; 
        /// 2) is not the same as start city.
        /// </summary>
        internal int FinishCity
        {
            get { return finishCity; }
            set
            {
                if ((value >= Constants.minCityNumber) ||
                    (value <= Constants.maxCityNumber))
                {
                    if (value != StartCity)
                    {
                        finishCity = value;
                    }
                }
            }
        }
        private int finishCity = 0;

        /// <summary>
        /// Keeps roads (edges) of transport system.
        /// </summary>
        private List<Road> roads = new List<Road>();

        public ReadOnlyCollection<Road> ReadOnlyRoads
        {
            get { return roads.AsReadOnly(); }
        }



        /// <summary>
        /// Gets data from input file. File lines should be filled according to task.
        /// Magic numbers in indices are set according to how lines should be inputed in task.
        /// </summary>
        /// <param name="fileName"> File with input data. </param>
        internal void GetData(string fileName)
        {
            string[] inputData = File.ReadAllLines(fileName);

            if (TryParseNumberOfCities(inputData[0], out numberOfCities)) return;
            if (TryParseNumberOfRoads(inputData[1], out numberOfRoads)) return;

            for (int roadIndex = 2; roadIndex < inputData.Length - 1; roadIndex++)
            {
                int from, to;
                RoadType roadType;
                float costOfTravel;

                string[] roadInfo = inputData[roadIndex].Split(' ');
                if (TryParseFromCity(roadInfo[0], out from)) return;
                if (TryParseToCity(roadInfo[1], out to)) return;
                if (!AreFromAndToCitiesDifferent(from, to)) return;
                if (TryParseRoadType(roadInfo[2], out roadType)) return;
                if (TryParseCostOfTravel(roadInfo[3], out costOfTravel)) return;

                Road road = new Road() { From = from, To = to, RoadType = roadType,
                                         CostOfTravel = costOfTravel };
                roads.Add(road);
            }

            string[] startAndFinishCity = inputData[inputData.Length - 1].Split(' ');
            if (TryParseStartCity(startAndFinishCity[0], out startCity)) return;
            if (TryParseFinishCity(startAndFinishCity[1], out finishCity)) return;
            if (AreStartAndFinishCitiesDifferent(startCity, finishCity)) return;
        }



        /// <summary>
        /// Checks that connected cities do not have same names.
        /// </summary>
        /// <param name="from"> City, from which road is coming out. </param>
        /// <param name="to"> City, to which road is coming in. </param>
        /// <returns>
        /// True: cities are different, continue retrieving data.
        /// False: cities have same name, show error message and interupt data reception.
        /// </returns>
        private bool AreFromAndToCitiesDifferent(int from, int to)
        {
            if (from != to) return true;

            EqualFromAndToCitiesErrorMessage();
            return false;
        }

        private void EqualFromAndToCitiesErrorMessage()
        {
            Console.WriteLine($"From-city and to-city can not be equal.");
        }

        /// <summary>
        /// Checks that start and finish cities do not have same names.
        /// </summary>
        /// <param name="start"> Start city. </param>
        /// <param name="finish"> Finish city. </param>
        /// <returns>
        /// True: cities are different, continue retrieving data.
        /// False: cities have same name, show error message and interupt data reception.
        /// </returns>
        private bool AreStartAndFinishCitiesDifferent(int start, int finish)
        {
            if (start != finish) return true;

            EqualStartAndFinishCitiesErrorMessage();
            return false;
        }

        private void EqualStartAndFinishCitiesErrorMessage()
        {
            Console.WriteLine($"Start city and finish city can not be equal.");
        }



        /// <summary>
        /// Tries casting inputed number of cities to int within set range.
        /// </summary>
        /// <param name="numberOfCitiesString"> Inputed number of cities. </param>
        /// <param name="numberOfCitesInt"> 
        /// If function returns true, assings inputed number of cities to numberOfCitiesInt.
        /// If function returns false, assigns -1 to numberOfCitiesInt.
        /// </param>
        /// <returns>
        /// Success: number of cities is valid, returns true.
        /// Failure: invalid number of cities, error message is shown, returns false.
        /// </returns>
        private bool TryParseNumberOfCities(string numberOfCitiesString, out int numberOfCitesInt)
        {
            if (int.TryParse(numberOfCitiesString, out numberOfCitesInt))
            {
                if ((numberOfCitesInt >= Constants.minNumberOfCities) &&
                    (numberOfCitesInt <= Constants.maxNumberOfCities))
                {
                    return true;
                }
            }

            NumberOfCitiesErrorMessage();
            numberOfCitesInt = -1;
            return false;
        }

        /// <summary>
        /// Writes to console error message with information about valid number of cities.
        /// </summary>
        private void NumberOfCitiesErrorMessage()
        {
            Console.WriteLine($"Invalid number of cities inputed. Should be within " +
                              $"range [{Constants.minNumberOfCities}; {Constants.maxNumberOfCities}]"); 
        }

        /// <summary>
        /// Tries casting inputed number of roads to int within set range.
        /// </summary>
        /// <param name="numberOfRoadsString"> Inputed number of roads. </param>
        /// <param name="numberOfRoadsInt"> 
        /// If function returns true, assings inputed number of roads to numberOfRoadsInt.
        /// If function returns false, assigns -1 to numberOfRoadsInt.
        /// </param>
        /// <returns>
        /// Success: number of roads is valid, returns true.
        /// Failure: invalid number of roads, error message is shown, returns false.
        /// </returns>
        private bool TryParseNumberOfRoads(string numberOfRoadsString, out int numberOfRoadsInt)
        {
            if (int.TryParse(numberOfRoadsString, out numberOfRoadsInt))
            {
                if ((numberOfRoadsInt >= MinNumberOfRoads) &&
                    (numberOfRoadsInt <= Constants.maxNumberOfRoads))
                {
                    return true;
                }
            }

            NumberOfRoadsErrorMessage();
            numberOfRoadsInt = -1;
            return false;
        }

        /// <summary>
        /// Writes to console error message with information about valid number of roads.
        /// </summary>
        private void NumberOfRoadsErrorMessage()
        {
            Console.WriteLine($"Invalid number of roads inputed. Should be within " +
                              $"range [{MinNumberOfRoads}; {Constants.maxNumberOfRoads}]");
        }

        /// <summary>
        /// Tries casting inputed from-city to int within set range.
        /// </summary>
        /// <param name="fromCityString"> Inputed from-city. </param>
        /// <param name="fromCityInt"> 
        /// If function returns true, assings inputed from-city to fromCityInt.
        /// If function returns false, assigns -1 to fromCityInt.
        /// </param>
        /// <returns>
        /// Success: from-city is valid, returns true.
        /// Failure: invalid from-city, error message is shown, returns false.
        /// </returns>
        private bool TryParseFromCity(string fromCityString, out int fromCityInt)
        {
            if (int.TryParse(fromCityString, out fromCityInt))
            {
                if ((fromCityInt >= Constants.minCityNumber) &&
                    (fromCityInt <= Constants.maxCityNumber))
                {
                    return true;
                }
            }

            FromCityErrorMessage();
            fromCityInt = -1;
            return false;
        }

        /// <summary>
        /// Writes to console error message with information about valid from-cities.
        /// </summary>
        private void FromCityErrorMessage()
        {
            Console.WriteLine($"Invalid from-city inputed. Should be within " +
                              $"range [{Constants.minCityNumber}; {Constants.maxCityNumber}] " +
                              $"and not equal to connected to-city.");
        }

        /// <summary>
        /// Tries casting inputed to-city to int within set range.
        /// </summary>
        /// <param name="toCityString"> Inputed to-city. </param>
        /// <param name="toCityInt"> 
        /// If function returns true, assings inputed to-city to toCityInt.
        /// If function returns false, assigns -1 to toCityInt.
        /// </param>
        /// <returns>
        /// Success: to-city is valid, returns true.
        /// Failure: invalid to-city, error message is shown, returns false.
        /// </returns>
        private bool TryParseToCity(string toCityString, out int toCityInt)
        {
            if (int.TryParse(toCityString, out toCityInt))
            {
                if ((toCityInt >= Constants.minCityNumber) &&
                    (toCityInt <= Constants.maxCityNumber))
                {
                    return true;
                }
            }

            ToCityErrorMessage();
            toCityInt = -1;
            return false;
        }

        /// <summary>
        /// Writes to console error message with information about valid to-cities.
        /// </summary>
        private void ToCityErrorMessage()
        {
            Console.WriteLine($"Invalid to-city inputed. Should be within " +
                              $"range [{Constants.minCityNumber}; {Constants.maxCityNumber}] " +
                              $"and not equal to connected from-city.");
        }

        /// <summary>
        /// Tries casting inputed road type to RoadType.
        /// </summary>
        /// <param name="roadTypeString"> Inputed road type. </param>
        /// <param name="roadType"> 
        /// If function returns true, assings inputed road type to roadType.
        /// If function returns false, assigns Invalid road type to roadType.
        /// </param>
        /// <returns>
        /// Success: roadType is valid, returns true.
        /// Failure: invalid roadType, error message is shown, returns false.
        /// </returns>
        private bool TryParseRoadType(string roadTypeString, out RoadType roadType)
        {
            int roadTypeKeeper;
            if (int.TryParse(roadTypeString, out roadTypeKeeper))
            {
                if ((roadTypeKeeper == (int)RoadType.Highway) ||
                    (roadTypeKeeper == (int)RoadType.Railway))
                {
                    roadType = (RoadType)roadTypeKeeper;
                    return true;
                }
            }

            RoadTypeErrorMessage();
            roadType = RoadType.Invalid;
            return false;
        }

        /// <summary>
        /// Writes to console error message with information about valid road type.
        /// </summary>
        private void RoadTypeErrorMessage()
        {
            Console.WriteLine($"Invalid road type inputed. Should be within " +
                              $"range [{RoadType.Highway}; {RoadType.Railway}]");
        }

        /// <summary>
        /// Tries casting inputed cost of travel to float within set range.
        /// </summary>
        /// <param name="costOfTravelString"> Inputed cost of travel. </param>
        /// <param name="costOfTravelFloat"> 
        /// If function returns true, assings inputed cost of travel to costOfTravelFloat.
        /// If function returns false, assigns -1 to costOfTravelFloat.
        /// </param>
        /// <returns>
        /// Success: cost of travel is valid, returns true.
        /// Failure: invalid cost of travel, error message is shown, returns false.
        /// </returns>
        private bool TryParseCostOfTravel(string costOfTravelString, out float costOfTravelFloat)
        {
            
            if (float.TryParse(costOfTravelString, out costOfTravelFloat))
            {
                if ((costOfTravelFloat >= Constants.minCost) &&
                    (costOfTravelFloat <= Constants.maxCost))
                {
                    return true;
                }
            }

            CostOfTravelErrorMessage();
            costOfTravelFloat = -1;
            return false;
        }

        /// <summary>
        /// Writes to console error message with information about valid cost of travel.
        /// </summary>
        private void CostOfTravelErrorMessage()
        {
            Console.WriteLine($"Invalid cost of travel inputed. Should be within " +
                              $"range ({Constants.minCost}; {Constants.maxCost}]");
        }

        /// <summary>
        /// Tries casting inputed start city to int within set range.
        /// </summary>
        /// <param name="startCityString"> Inputed start city. </param>
        /// <param name="startCityInt"> 
        /// If function returns true, assings inputed start city to startCityInt.
        /// If function returns false, assigns -1 to startCityInt.
        /// </param>
        /// <returns>
        /// Success: start city is valid, returns true.
        /// Failure: invalid start city, error message is shown, returns false.
        /// </returns>
        private bool TryParseStartCity(string startCityString, out int startCityInt)
        {
            if (int.TryParse(startCityString, out startCityInt))
            {
                if ((startCityInt >= Constants.minCityNumber) &&
                    (startCityInt <= Constants.maxCityNumber))
                {
                    return true;
                }
            }

            StartCityErrorMessage();
            startCityInt = -1;
            return false;
        }

        /// <summary>
        /// Writes to console error message with information about valid start city.
        /// </summary>
        private void StartCityErrorMessage()
        {
            Console.WriteLine($"Invalid start city inputed. Should be within " +
                              $"range [{Constants.minCityNumber}; {Constants.maxCityNumber}] " +
                              $"and not equal to finish city.");
        }

        /// <summary>
        /// Tries casting inputed finish city to int within set range.
        /// </summary>
        /// <param name="finishCityString"> Inputed finish city. </param>
        /// <param name="finishCityInt"> 
        /// If function returns true, assings inputed finish city to startCityInt.
        /// If function returns false, assigns -1 to startCityInt.
        /// </param>
        /// <returns>
        /// Success: finish city is valid, returns true.
        /// Failure: invalid finish city, error message is shown, returns false.
        /// </returns>
        private bool TryParseFinishCity(string finishCityString, out int finishCityInt)
        {
            if (int.TryParse(finishCityString, out finishCityInt))
            {
                if ((finishCityInt >= Constants.minCityNumber) &&
                    (finishCityInt <= Constants.maxCityNumber))
                {
                    return true;
                }
            }

            FinishCityErrorMessage();
            finishCityInt = -1;
            return false;
        }

        /// <summary>
        /// Writes to console error message with information about valid finish city.
        /// </summary>
        private void FinishCityErrorMessage()
        {
            Console.WriteLine($"Invalid finish city inputed. Should be within " +
                              $"range [{Constants.minCityNumber}; {Constants.maxCityNumber}] " +
                              $"and not equal to start city.");
        }
    }
}
