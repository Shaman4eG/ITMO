using System;
using System.Collections.Generic;

namespace lab2OP
{
    class Program
    {
        static void Main()
       {
            bool repeat = true;
            int menuItemNumber;
            List<Employee> employees = new List<Employee>();

            while (repeat)
            {
                EmployeeDataBase.ShowMenu();
                menuItemNumber = Input();
                EmployeeDataBase.ChooseMenuItem(menuItemNumber, employees);
            }
        }

        private static int Input()
        {
            int menuItemNumber = 0;
            bool isNum;
            bool repeat = true;

            while (repeat)  // Повторять, пока не будет получен валидный ввод
            {
                isNum = int.TryParse(Console.ReadLine(), out menuItemNumber);   // Проверяем, что ввели число
                if (!isNum)
                {
                    Console.WriteLine("Invalid input.");
                    continue;
                }
                else if ((menuItemNumber < 1) || (menuItemNumber > 5))  // Проверяем, что введенное число является одним из пунктов меню
                {
                    Console.WriteLine("Invalid input.");
                    continue;
                }
                repeat = false;
            }
            return menuItemNumber;
        }
    }

    class Employee
    {
        public int SpecialNumber { get; set; }
        public string Name { get; set; }
        public string LastName { get; set; }
        public string Patronymic { get; set; }
        public string BirthDate { get; set; }
        public string Position { get; set; }

        public Employee(int specialNumberPar)
        {
            SpecialNumber = specialNumberPar;
        }
    }

    class EmployeeDataBase
    {
        private static bool NeedClear { get; set; } = true;
        private static int SpecialNumberGenerator { get; set; } = 1;

        public static void ShowMenu()
        {
            if (NeedClear)
            {
                Console.Clear();
                Console.WriteLine("1. Посмортреть список сотрудников\n2. Добавить сотрудника\n3. Удалить сотрудника\n4. Найти сотрудника\n5. Выйти\n");
            }
            NeedClear = true;
        }

        private enum MenuItems
        {
            ShowEmployeesListEnum = 1,
            AddEmployeeEnum,
            DeleteEmployeeEnum,
            FindEmployeeEnum,
            ExitEnum
        }

        public static void ChooseMenuItem(int menuItemNumber, List<Employee> employees)
        {
            MenuItems menuItemNumberEnum = (MenuItems)menuItemNumber;
            switch (menuItemNumberEnum)
            {
                case MenuItems.ShowEmployeesListEnum:
                    ShowEmployeesList(employees);
                    break;

                case MenuItems.AddEmployeeEnum:
                    AddEmployee(employees);
                    break;

                case MenuItems.DeleteEmployeeEnum:
                    DeleteEmployee(employees);
                    break;

                case MenuItems.FindEmployeeEnum:
                    FindEmployee(employees);
                    break;

                case MenuItems.ExitEnum:
                    Environment.Exit(0);
                    break;
            }
        }

        private static void ShowEmployeesList(List<Employee> employees)
        {
            for (int i = 0; i < employees.Count; i++)
                Console.WriteLine(employees[i].SpecialNumber + " | " + employees[i].Name + " | " + employees[i].LastName + " | " +
                                  employees[i].Patronymic + " | " + employees[i].BirthDate + " | " + employees[i].Position);
            Console.WriteLine();
            NeedClear = false;
        }

        private static void AddEmployee(List<Employee> employees)
        {
            Employee newEmployee = new Employee(SpecialNumberGenerator++);

            Console.Write("Employee's name: ");
            newEmployee.Name = Console.ReadLine();
            Console.Write("Employee's lastname: ");
            newEmployee.LastName = Console.ReadLine();
            Console.Write("Employee's patronymic: ");
            newEmployee.Patronymic = Console.ReadLine();
            Console.Write("Employee's birth date: ");
            newEmployee.BirthDate = Console.ReadLine();
            Console.Write("Employee's position: ");
            newEmployee.Position = Console.ReadLine();

            Console.WriteLine();
            employees.Add(newEmployee);
        }

        private static void DeleteEmployee(List<Employee> employees)
        {
            bool repeat = true;
            bool isNum;
            int specialNumberOfEmployeeToDelete;
            List<int> foundEmployeesIndexes = new List<int>();
            int indexOfEmployeeToDelete = 0;
            int numberOfEmployeesFound = FindEmployee(employees, foundEmployeesIndexes);
            if (numberOfEmployeesFound > 0)
            {
                Console.WriteLine("\nTo delete an employee write employee's number from first column or write '0' to go back to menu.");
      
                while (repeat)  // Повторять, пока не будет получен валидный ввод
                {
                    isNum = int.TryParse(Console.ReadLine(), out specialNumberOfEmployeeToDelete);   // Проверяем, что ввели число
                    if (!isNum)
                    {
                        Console.WriteLine("Invalid input.");
                        continue;
                    }

                    if (specialNumberOfEmployeeToDelete != 0)
                    {
                        int i;
                        for (i = 0; i < numberOfEmployeesFound; i++)    // Проверяем, что введенное число соответствует номеру одного из сотрудников
                            if (specialNumberOfEmployeeToDelete == employees[foundEmployeesIndexes[i]].SpecialNumber)
                            {
                                indexOfEmployeeToDelete = foundEmployeesIndexes[i];
                                i = numberOfEmployeesFound + 1;
                            }
                        if (i > numberOfEmployeesFound)
                        {
                            employees.RemoveAt(indexOfEmployeeToDelete);
                            Console.WriteLine("\nEmployee successfully deleted.");
                        }
                        else
                        {
                            Console.WriteLine("No employee with such special number was found. Try again or write '0' to go back to menu.");
                            continue;
                        }
                    }
                    else
                        NeedClear = true;

                    repeat = false;
                }
                Console.WriteLine();
            }
        }

        private static void FindEmployee(List<Employee> employees)
        {
            NeedClear = false;
            List<int> foundEmployeesIndexes = new List<int>();  // Создаем список, в котором будут хранится индексы сотрудников с указанной фамилией
            Console.Write("Input employee's lastname: ");
            string employeeToFind = Console.ReadLine();

            for (int i = 0; i < employees.Count; i++)   // Ищем все совпадения фамилий в списке
                if (employeeToFind == employees[i].LastName)
                    foundEmployeesIndexes.Add(i);
            if (foundEmployeesIndexes.Count > 0)    // Выводим всех найденных сотрудников
                for (int i = 0; i < foundEmployeesIndexes.Count; i++)
                    Console.WriteLine(employees[foundEmployeesIndexes[i]].SpecialNumber + " | " + employees[foundEmployeesIndexes[i]].Name + " | "
                                      + employees[foundEmployeesIndexes[i]].LastName + " | " + employees[foundEmployeesIndexes[i]].Patronymic + 
                                      " | " + employees[foundEmployeesIndexes[i]].BirthDate + " | " 
                                      + employees[foundEmployeesIndexes[i]].Position);
            else
                Console.WriteLine("No employee with such lastname was found.");
            Console.WriteLine();
        }

        private static int FindEmployee(List<Employee> employees, List<int> foundEmployeesIndexes)
        {
            NeedClear = false;
            Console.Write("Input employee's lastname: ");
            string employeeToFind = Console.ReadLine();

            for (int i = 0; i < employees.Count; i++)   // Ищем все совпадения фамилий в списке
                if (employeeToFind == employees[i].LastName)
                    foundEmployeesIndexes.Add(i);
            if (foundEmployeesIndexes.Count > 0)    // Выводим всех найденных сотрудников
                for (int i = 0; i < foundEmployeesIndexes.Count; i++)
                    Console.WriteLine(employees[foundEmployeesIndexes[i]].SpecialNumber + " | " + employees[foundEmployeesIndexes[i]].Name + " | "
                                      + employees[foundEmployeesIndexes[i]].LastName + " | " + employees[foundEmployeesIndexes[i]].Patronymic +
                                      " | " + employees[foundEmployeesIndexes[i]].BirthDate + " | "
                                      + employees[foundEmployeesIndexes[i]].Position);
            else
                Console.WriteLine("No employee with such lastname was found.");

            Console.WriteLine();
            return foundEmployeesIndexes.Count;
        }
    }
}
