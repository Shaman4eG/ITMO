using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;

namespace CheapestPath
{
    class Output
    {
        public float cheapestTraveCost { get; set; }

        private List<ElementOfPath> shortestPath;

        public void SetShortestPath(List<ElementOfPath> newShortestPath)
        {
            shortestPath = newShortestPath;
        }

        internal ReadOnlyCollection<ElementOfPath> ReadOnlyShortestPath
        {
            get { return shortestPath.AsReadOnly(); }
        }



        public void OutputData(int finishCity)
        {
            string[] outputData = new string[2 + shortestPath.Count];

            outputData[0] = String.Format("{0:0.00}", cheapestTraveCost);
            for (int i = 0; i < shortestPath.Count; i++)
            {
                outputData[i + 1] = shortestPath[i].ParentCity + " " + shortestPath[i].CameOnSuchRoad;
            }
            outputData[outputData.Length - 1] = finishCity.ToString();

            File.WriteAllLines("../../Output/TOUR.OUT.txt", outputData);
        }
    }
}
