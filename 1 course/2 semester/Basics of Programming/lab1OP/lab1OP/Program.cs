using System;
using System.Collections;
using Print = System.Console;

namespace lab1OP
{
    class Program
    {
        static int Main()
        {
            // ArrayList
            Print.WriteLine("ArrayList");
            ArrayList aList = new ArrayList();
            Random rand = new Random();
            double randForArrList;
            for (int i = 0; i < 5; i++)
            {
                randForArrList = (double)(rand.Next(1000))/11;
                aList.Add(randForArrList);
            }

            foreach (object o in aList)
                Print.Write("{0:#.##}  ", o);
            Print.WriteLine();

            aList.RemoveAt(1);
            foreach (object o in aList)
                Print.Write("{0:#.##}  ", o);

            // Queue
            Print.WriteLine("\n\nQueue");

            Queue queueNumbers = new Queue();

            queueNumbers.Enqueue(3);
            queueNumbers.Enqueue(5);
            queueNumbers.Enqueue(7);

            int number = (int)queueNumbers.Dequeue();
            Print.WriteLine("First order in queue was " + number);
            number = (int)queueNumbers.Peek();
            Print.WriteLine("First order in queue is " + number);

            // Stack
            Print.WriteLine("\nStack");

            Stack stackNumbers = new Stack();

            stackNumbers.Push(3);
            stackNumbers.Push(5);
            stackNumbers.Push(7);

            int stackNumber = (int)stackNumbers.Pop();
            Print.WriteLine(stackNumber + " was on top of the stack");
            stackNumber = (int)stackNumbers.Peek();
            Print.WriteLine(stackNumber + " is on top of the stack");

            // Hashtable
            Print.WriteLine("\nHashtable");
            Hashtable ages = new Hashtable();       

            ages.Add("Scott", 25);
            ages.Add("Sam", 6);
            ages.Add("Jisun", 25);

            if (ages.ContainsKey("Scott"))
            {
                int scottsAge = (int)ages["Scott"];
                Print.WriteLine("Scott is " + scottsAge.ToString());
            }
            else
                Print.WriteLine("Scott is not in the hash table...");

            ages.Remove("Jisun");


            foreach (string key in ages.Keys)
                Print.WriteLine("Value at ages[\"" + key + "\"] = " + ages[key].ToString());

            Print.ReadKey();
            return 0;
        }
    }
}
