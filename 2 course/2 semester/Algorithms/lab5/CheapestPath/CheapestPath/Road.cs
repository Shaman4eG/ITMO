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
            get { return From; }
            set
            {
                if ((value >= Constants.minCityNumber) ||
                    (value <= Constants.maxCityNumber))
                {
                    if (value != To)
                    {
                        From = value;
                    }
                }
            }
        }

        /// <summary>
        /// City, to which road is coming in.
        /// Sets only if: 
        /// 1) city number is in list of possible city numbers; 
        /// 2) is not the same as city, from which road is coming out. 
        /// </summary>
        internal int To
        {
            get { return To; }
            set
            {
                if ((value >= Constants.minCityNumber) ||
                    (value <= Constants.maxCityNumber))
                {
                    if (value != From)
                    {
                        To = value;
                    }
                }
            }
        }

        /// <summary>
        /// Effects cost of travelling through road.
        /// Sets only if:
        /// 1) there is such a road type.
        /// </summary>
        internal RoadType RoadType
        {
            get { return RoadType; }
            set
            {
                if ((value == RoadType.Highway) ||
                    (value == RoadType.Railway))
                {
                    RoadType = value;
                }
            }
        }

        /// <summary>
        /// Depends on road type.
        /// Sets only if:
        /// 1) cost is withing preset range.
        /// </summary>
        internal float CostOfTravel
        {
            get { return CostOfTravel; }
            set
            {
                if ((value > Constants.minCost) &&
                    (value <= Constants.maxCost))
                {
                    CostOfTravel = value;
                }
            }
        }
    }
}
