namespace CheapestPath
{
    /// <summary>
    /// Keeps globally used constants in CheapestPath solution.
    /// </summary>
    class Constants
    {
        // SECTION START: consts for input.
        internal const int minNumberOfCities = 2;
        internal const int maxNumberOfCities = 100;

        internal static readonly int minNumberOfRoads;
        internal const int maxNumberOfRoads = 1000;
        // SECTION END

        // SECTION START: regex for input checking

        // SECTION END
        
        internal const int minCityNumber = 1;
        internal const int maxCityNumber = 100;

        /// <summary>
        /// Excluding
        /// </summary>
        internal const float minCost = 0f;
        internal const float maxCost = 1000f;

        /// <summary>
        /// Should be multiplied by travel through road cost. 
        /// </summary>
        internal const float insuranceCoefficient = 0.1f;
    } 
}
