using System;
using System.Collections.Generic;

namespace lab4OP
{
    class Program
    {
        static void Main()
        {
            Console.WriteLine(new HeadOfDepartment(2));
            return;

            bool repeat = true;
            int menuItemNumber;
            EmployeeDataBase mainDataBase = new EmployeeDataBase();
            List<Employee> employees = mainDataBase.GetList();
            EmployeeDataBase abstractEmployeesDataBase = new EmployeeDataBase();
            List<Employee> abstractEmployees = CreateAbstractEmployeesList(abstractEmployeesDataBase);

            while (repeat)
            {
                mainDataBase.ShowMenu(employees);
                menuItemNumber = Input(9);
                mainDataBase.ChooseMenuItem(menuItemNumber, employees, abstractEmployees);
            }
        }

        public static int Input(int menuNumberUpperBound)
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
                else if ((menuItemNumber < 1) || (menuItemNumber > menuNumberUpperBound))  // Проверяем, что введенное число является одним из пунктов меню
                {
                    Console.WriteLine("Invalid input.");
                    continue;
                }
                repeat = false;
            }
            return menuItemNumber;
        }

        private static List<Employee> CreateAbstractEmployeesList(EmployeeDataBase abstractEmployeesDataBase)   // Нужен для вывода отдельных групп работников.
        {                                                                                                       // Используется в EmployeeDataBase.GetGroupOfEmployees
            List<Employee> abstractEmployees = abstractEmployeesDataBase.GetList();
            abstractEmployees.Add(new HeadOfDepartment(6));
            abstractEmployees.Add(new OfficeWorker(7));
            abstractEmployees.Add(new CleaningStaff(8));
            return abstractEmployees;
        }
    }



    abstract class Employee : IComparable<Employee>, IEquatable<Employee>
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

        public abstract override string ToString();

        public bool Equals(Employee other)
        {
            if (other == null)
                return false;
            return (this.Position.Equals(other.Position));
        }

        public override int GetHashCode()
        {
            return this.Position.GetHashCode();
        }

        public override bool Equals(object obj)
        {
            Employee emp = obj as Employee;
            if (emp != null)
            {
                return Equals(emp);
            }
            else
            {
                return false;
            }
        }
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


        // Так как abstractEmployees имеет три элемента, расположенных в ячейках 0, 1 и 2, то,
        // дабы корректно обратиться к одому из них, мы вычитаем 5 (количество предшествующих пунктов меню)
        // из указанного пункта меню.
        private List<Employee> GetGroupOfEmployees<T>(int menuItemNumber, T employees, T abstractEmployees)
            where T : List<Employee>
        {
            List<Employee> employeesOfGroupToFind = default(T);
            employeesOfGroupToFind = new List<Employee>();
            for (int i = 0; i < employees.Count; i++)
                if (employees[i].Equals(abstractEmployees[menuItemNumber - 5]))
                    employeesOfGroupToFind.Add(employees[i]);
            return employeesOfGroupToFind;
        }



        public void ShowMenu(List<Employee> employees)
        {
            if (NeedClear)
            {
                Console.Clear();
                Console.WriteLine("1. Посмортреть список сотрудников\n2. Добавить сотрудника\n3. Удалить сотрудника\n4. Найти сотрудника\n5. Найти работников на позиции \"Head of Department\"\n6. Найти работников на позиции \"Office Worker\"\n7. Найти работников на позиции \"Cleaning Staff\"\n8. Особые свойства\n9. Выйти\n");
                if (AddEmployeeWasLastAction)
                {
                    for (int i = 0; i < employees.Count; i++)   // Ищем индекс последнего добавленного работника, чтобы вывести сообщение о его добавлении.
                        if (employees[i].SpecialNumber == SpecialNumberGenerator - 1)
                        {
                            Console.WriteLine("New " + employees[i].ToString() + " successfully added!\n");
                            AddEmployeeWasLastAction = false;
                            i = employees.Count;
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
            ShowHeadsOfDepartmentsListEnum,
            ShowOfficeWorkersListEnum,
            ShowCleaningStaffListEnum,
            SpecialPropertiesEnum,
            ExitEnum
        }

        public void ChooseMenuItem(int menuItemNumber, List<Employee> employees, List<Employee> abstractEmployees)
        {
            MenuItems menuItemNumberEnum = (MenuItems)menuItemNumber;
            switch (menuItemNumberEnum)
            {
                case MenuItems.ShowEmployeesListEnum:
                    ShowEmployeesList(employees, false);
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

                case MenuItems.ShowHeadsOfDepartmentsListEnum:
                    List<Employee> employeesOfGroupToFind = GetGroupOfEmployees(menuItemNumber, employees, abstractEmployees);
                    if (employeesOfGroupToFind.Count > 0)
                        ShowEmployeesList(employeesOfGroupToFind, false);
                    else
                        ShowEmployeesList(employeesOfGroupToFind, true);
                    break;

                case MenuItems.ShowOfficeWorkersListEnum:
                    List<Employee> employeesOfGroupToFind2 = GetGroupOfEmployees(menuItemNumber, employees, abstractEmployees);
                    if (employeesOfGroupToFind2.Count > 0)
                        ShowEmployeesList(employeesOfGroupToFind2, false);
                    else
                        ShowEmployeesList(employeesOfGroupToFind2, true);
                    break;

                case MenuItems.ShowCleaningStaffListEnum:
                    List<Employee> employeesOfGroupToFind3 = GetGroupOfEmployees(menuItemNumber, employees, abstractEmployees);
                    if (employeesOfGroupToFind3.Count > 0)
                        ShowEmployeesList(employeesOfGroupToFind3, false);
                    else
                        ShowEmployeesList(employeesOfGroupToFind3, true);
                    break;

                case MenuItems.SpecialPropertiesEnum:
                    TheInsAndOuts shower = new TheInsAndOuts();
                    shower.DemonstrationOfSpecialProperties();
                    break;

                case MenuItems.ExitEnum:
                    Environment.Exit(0);
                    break;
            }
        }

        private void ShowEmployeesList(List<Employee> employees, bool isEmpty)
        {
            for (int i = 0; i < employees.Count; i++)
                Console.WriteLine(employees[i].SpecialNumber + " | " + employees[i].Name + " | " + employees[i].LastName + " | " +
                                  employees[i].Patronymic + " | " + employees[i].BirthDate + " | " + employees[i].Position);
            if (isEmpty)
                Console.WriteLine("No employees of such group were found.");

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
            {
                for (int i = 0; i < foundEmployeesIndexes.Count; i++)
                {
                    var emp = employees[foundEmployeesIndexes[i]];
                    Console.WriteLine(string.Join(" | ", emp.SpecialNumber, emp.Name, emp.LastName, emp.Patronymic, emp.BirthDate, emp.Position));
                }
            }
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
                {
                    var emp = employees[foundEmployeesIndexes[i]];
                    Console.WriteLine(string.Join(" | ", emp.SpecialNumber, emp.Name, emp.LastName, emp.Patronymic, emp.BirthDate, emp.Position));
                }
            else
                Console.WriteLine("No employee with such lastname was found.");

            Console.WriteLine();
            return foundEmployeesIndexes.Count;
        }

    }

    public interface ICovariant<out T> { }
    public interface IContravariant<in T> { }

    public class Covariant<T> : ICovariant<T> { }
    public class Contravariant<T> : IContravariant<T> { }

    public class Fruit { }
    public class Apple : Fruit { }

    public class TheInsAndOuts
    {
        public void DemonstrationOfSpecialProperties()
        {
            Covariance();
            Contravariance();
            BoxUnbox();
        }

        public void Covariance()
        {
            ICovariant<Fruit> fruit = new Covariant<Fruit>();
            ICovariant<Apple> apple = new Covariant<Apple>();

            Covariant(fruit);
            Covariant(apple); // !
        }

        public void Contravariance()
        {
            IContravariant<Fruit> fruit = new Contravariant<Fruit>();
            IContravariant<Apple> apple = new Contravariant<Apple>();

            Contravariant(fruit); // !
            Contravariant(apple);
        }

        public void BoxUnbox()
        {
            int x = 44;
            System.Collections.ArrayList array = new System.Collections.ArrayList();
            array.Add(x); // Упаковка значения x в тип Object
            int y = (int)array[0]; // Распаковка в значение типа int первого элемента коллекции
        }

        public void Covariant(ICovariant<Fruit> fruit)
        { }

        public void Contravariant(IContravariant<Apple> apple)
        { }
    }
}