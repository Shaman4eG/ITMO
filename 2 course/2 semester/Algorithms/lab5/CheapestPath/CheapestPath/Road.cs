using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
    }
}
