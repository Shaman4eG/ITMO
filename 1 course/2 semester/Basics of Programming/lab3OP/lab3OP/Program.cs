using System;
using System.Collections.Generic;

namespace lab4OP
{
    class Program
    {
        static void Main()
        {
            bool repeat = true;
            int menuItemNumber;
            EmployeeDataBase mainDataBase = new EmployeeDataBase();
            List<Employee> employees = mainDataBase.GetList();

            while (repeat)
            {
                mainDataBase.ShowMenu(employees);
                menuItemNumber = Input(5);
                mainDataBase.ChooseMenuItem(menuItemNumber, employees);
            }
        }

        public static int Input(int menuNumberUpperBound)
        {
            int menuItemNumber;
            bool isNum;

            do  // Повторять, пока не будет получен валидный ввод
            {
                isNum = int.TryParse(Console.ReadLine(), out menuItemNumber);   // Проверяем, что ввели число
                if (!isNum)
                {
                    Console.WriteLine("Invalid input.");
                    continue;
                }
                else if ((menuItemNumber < 1) || (menuItemNumber > menuNumberUpperBound))  // Проверяем, что введенное число является одним из пунктов меню
                {
                    Console.WriteLine("Invalid input.");
                    continue;
                }
            } while (false);

            return menuItemNumber;
        }
    }

    abstract class Employee : IComparable<Employee>
    {
        public int SpecialNumber { get; set; }
        public string Name { get; set; }
        public string LastName { get; set; }
        public string Patronymic { get; set; }
        public string BirthDate { get; set; }
        public abstract string Position { get; set; }

        public Employee(int specialNumberPar)
        {
            SpecialNumber = specialNumberPar;
        }

        public int CompareTo(Employee emp)
        {
            return this.Position.CompareTo(emp.Position);
        }

        // ПЕРЕД РАСКОММЕТНИРОВАНИЕМ УБРАТЬ ОБОБЩЕННИЕ У IComparable В Employee
        // Реализация CompareTo с "as"
        /*
        public int CompareTo(object o)
        {
            Employee empToCompare = o as Employee;
            if (empToCompare != null)
                return this.Position.CompareTo(empToCompare.Position);
            else
                throw new Exception("Невозможно сравнить два объекта.");
        }
        */

        // Реализация CompareTo с "is" 
        /*
        public int CompareTo(object o)
        {
            Employee empToCompare;
            if (o is Employee)
            {
                empToCompare = o as Employee;
                return this.Position.CompareTo(empToCompare.Position);
            }
            else
                throw new Exception("Невозможно сравнить два объекта.");
        }
        */

        public abstract string ToString();
    }


    // ВИДЫ РАБОТНИКОВ

    class HeadOfDepartment : Employee
    {
        public override string Position { get; set; } = "Head of Department";

        public HeadOfDepartment(int specialNumberPar) : base(specialNumberPar)
        { }

        public override string ToString()
        {
            return "Head of Department";
        }
    }

    class OfficeWorker : Employee
    {
        public override string Position { get; set; } = "Office worker";

        public OfficeWorker(int specialNumberPar) : base(specialNumberPar)
        { }

        public override string ToString()
        {
            return "Office Worker";
        }
    }

    class CleaningStaff : Employee
    {
        public override string Position { get; set; } = "Cleaning staff";

        public CleaningStaff(int specialNumberPar) : base(specialNumberPar)
        { }

        public override string ToString()
        {
            return "Cleaning Staff";
        }
    }




    class EmployeeDataBase
    {
        public List<Employee> GetList()
        {
            return employees;
        }

        private List<Employee> employees = new List<Employee>();
        private bool NeedClear { get; set; } = true;
        private int SpecialNumberGenerator { get; set; } = 1;
        private bool AddEmployeeWasLastAction = false;

        public void ShowMenu(List<Employee> employees)
        {
            if (NeedClear)
            {
                Console.Clear();
                Console.WriteLine("1. Посмортреть список сотрудников\n2. Добавить сотрудника\n3. Удалить сотрудника\n4. Найти сотрудника\n5. Выйти\n");
                if (AddEmployeeWasLastAction)
                {
                    for (int i = 0; i < employees.Count; i++)   // Ищем индекс последнего добавленного работника, чтобы вывести сообщение о его добавлении.
                    {
                        if (employees[i].SpecialNumber == SpecialNumberGenerator - 1)
                        {
                            Console.WriteLine("New " + employees[i].ToString() + " successfully added!\n");
                            AddEmployeeWasLastAction = false;
                            i = employees.Count;
                        }
                    }
                }
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

        public void ChooseMenuItem(int menuItemNumber, List<Employee> employees)
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

        private void ShowEmployeesList(List<Employee> employees)
        {
            for (int i = 0; i < employees.Count; i++)
                Console.WriteLine(employees[i].SpecialNumber + " | " + employees[i].Name + " | " + employees[i].LastName + " | " +
                                  employees[i].Patronymic + " | " + employees[i].BirthDate + " | " + employees[i].Position);
            Console.WriteLine();
            NeedClear = false;
        }

        private enum EmployeesTypes
        {
            HeadOfDepartmentEnum = 1,
            OfficeWorkerEnum,
            CleaningStaffEnum
        }

        private void AddEmployee(List<Employee> employees)
        {
            AddEmployeeWasLastAction = true;
            Console.WriteLine("Choose employees position:\n\n1. Head of Department\n2. Office Worker\n3. Cleaning Staff\n");
            EmployeesTypes menuItemNumber = (EmployeesTypes)Program.Input(3);
            Employee newEmployee = new HeadOfDepartment(SpecialNumberGenerator);
            switch (menuItemNumber)
            {
                case EmployeesTypes.HeadOfDepartmentEnum:
                    newEmployee = new HeadOfDepartment(SpecialNumberGenerator++);
                    break;

                case EmployeesTypes.OfficeWorkerEnum:
                    newEmployee = new OfficeWorker(SpecialNumberGenerator++);
                    break;

                case EmployeesTypes.CleaningStaffEnum:
                    newEmployee = new CleaningStaff(SpecialNumberGenerator++);
                    break;
            }

            Console.Write("Employee's name: ");
            newEmployee.Name = Console.ReadLine();
            Console.Write("Employee's lastname: ");
            newEmployee.LastName = Console.ReadLine();
            Console.Write("Employee's patronymic: ");
            newEmployee.Patronymic = Console.ReadLine();
            Console.Write("Employee's birth date: ");
            newEmployee.BirthDate = Console.ReadLine();

            Console.WriteLine();
            employees.Add(newEmployee);
            employees.Sort();
        }

        private void DeleteEmployee(List<Employee> employees)
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

        private void FindEmployee(List<Employee> employees)
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

        private int FindEmployee(List<Employee> employees, List<int> foundEmployeesIndexes)  // Перегрузка метода FindEmployee для метода DeleteEmployee
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
