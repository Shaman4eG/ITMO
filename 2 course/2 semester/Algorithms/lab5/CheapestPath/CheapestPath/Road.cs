namespace CheapestPath
{
    /// <summary>
    /// Reresents graph's edge. 
    /// Keeps information about:
    /// 1) City, from which road is coming out.
    /// 2) City, to which road is coming in.
    /// 3) Road type.
    /// 4) Cost of travel.
    /// </summary>
    class Road
    {
        /// <summary>
        /// City, from which road is coming out.
        /// Sets only if: 
        /// 1) city number is in list of possible city numbers; 
        /// 2) is not the same as city, to which road is coming in. 
        /// </summary>
        internal int From
        {
            get { return from; }
            set
            {
                if ((value >= Constants.minCityNumber) ||
                    (value <= Constants.maxCityNumber))
                {
                    if (value != To)
                    {
                        from = value;
                    }
                }
            }
        }
        private int from = 0;

        /// <summary>
        /// City, to which road is coming in.
        /// Sets only if: 
        /// 1) city number is in list of possible city numbers; 
        /// 2) is not the same as city, from which road is coming out. 
        /// </summary>
        internal int To
        {
            get { return to; }
            set
            {
                if ((value >= Constants.minCityNumber) ||
                    (value <= Constants.maxCityNumber))
                {
                    if (value != From)
                    {
                        to = value;
                    }
                }
            }
        }
        private int to = 0;

        /// <summary>
        /// Effects cost of travelling through road.
        /// Sets only if:
        /// 1) there is such a road type.
        /// </summary>
        internal RoadType RoadType
        {
            get { return roadType; }
            set
            {
                if ((value == RoadType.Highway) ||
                    (value == RoadType.Railway))
                {
                    roadType = value;
                }
            }
        }
        private RoadType roadType = RoadType.Invalid;

        /// <summary>
        /// Depends on road type.
        /// Sets only if:
        /// 1) cost is withing predefined range.
        /// </summary>
        internal float CostOfTravel
        {
            get { return costOfTravel; }
            set
            {
                if ((value > Constants.minCost) &&
                    (value <= Constants.maxCost))
                {
                    costOfTravel = value;
                }
            }
        }
        private float costOfTravel = 0;

        /// <summary>
        /// Set during shortest path finding. 
        /// If true - from-city is a parent of to-city in lowest cost path.
        /// </summary>
        internal bool FromCityIsParent { get; set; } = false;



        /// <summary>
        /// Tries casting to Road and comparing roads. Two roads are 
        /// equal when from-cities are the same and to-cities are the same.
        /// </summary>
        /// <param name="obj"> Object to compare with. </param>
        /// <returns>
        /// True: equal.
        /// False: inequal.
        /// </returns>
        public override bool Equals(System.Object obj)
        {
            // If parameter is null return false.
            if (obj == null)
            {
                return false;
            }

            // If parameter cannot be cast to Road return false.
            Road road = obj as Road;
            if (road == null)
            {
                return false;
            }

            // Return true if the fields match:
            return (from == road.from) && (to == road.to);
        }

        /// <summary>
        /// Compares roads. equal when from-cities are the same and to-cities are the same.
        /// </summary>
        /// <param name="road"> Road to compare with. </param>
        /// <returns>
        /// True: equal.
        /// False: inequal.
        /// </returns>
        public bool Equals(Road road)
        {
            // If parameter is null return false:
            if (road == null)
            {
                return false;
            }

            // Return true if the fields match:
            return (from == road.from) && (to == road.to);
        }
    }
}
