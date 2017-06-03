using System;
using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;
using System.Xml;
using System.Text.RegularExpressions;
using System.Xml.Schema;


namespace lab4OP
{
    public class Program
    {
        static void Main()
        {
            int menuItemNumber;
            EmployeeDataBase mainDataBase = new EmployeeDataBase();
            List<Employee> employees = mainDataBase.GetList();

            EmployeeDataBase abstractEmployeesDataBase = new EmployeeDataBase();
            List<Employee> abstractEmployees = CreateAbstractEmployeesList(abstractEmployeesDataBase);

            int numOfMenuItems = Enum.GetNames(typeof(EmployeeDataBase.MenuItems)).Length;

            bool repeatMain = true;

            while (repeatMain)
            {
                mainDataBase.ShowMenu(employees);
                menuItemNumber = Input(numOfMenuItems);
                mainDataBase.ChooseMenuItem(menuItemNumber, ref employees, abstractEmployees, ref repeatMain);
            }
        }

        public static int Input(int menuNumberUpperBound)
        {
            int menuItemNumber = 0;
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
            }
            while (false);

            return menuItemNumber;
        }

        private static List<Employee> CreateAbstractEmployeesList(EmployeeDataBase abstractEmployeesDataBase)   // Нужен для вывода отдельных групп работников.
        {                                                                                                       // Используется в EmployeeDataBase.GetGroupOfEmployees
            List<Employee> abstractEmployees = new List<Employee>();
            abstractEmployees.Add(new HeadOfDepartment((int)EmployeeDataBase.MenuItems.ShowHeadsOfDepartmentsListEnum));
            abstractEmployees.Add(new OfficeWorker((int)EmployeeDataBase.MenuItems.ShowHeadsOfDepartmentsListEnum));
            abstractEmployees.Add(new CleaningStaff((int)EmployeeDataBase.MenuItems.ShowCleaningStaffListEnum));
            return abstractEmployees;
        }
    }

    [Serializable]
    public class Employee : IComparable<Employee>, IEquatable<Employee>
    {
        public int SpecialNumber { get; set; }
        public string Name { get; set; }
        public string LastName { get; set; }
        public string Patronymic { get; set; }
        public string BirthDate { get; set; }
        public virtual string Position { get; set; }

        public Employee()
        { }

        public Employee(int specialNumberPar)
        {
            SpecialNumber = specialNumberPar;
        }

        public virtual string NameForXML()
        {
            return "Employee";
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

        public override string ToString()
        {
            return "Employee";
        }

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

    [Serializable]
    public class HeadOfDepartment : Employee
    {
        public HeadOfDepartment()
        { }

        public override string Position { get; set; } = "Head of Department";

        public HeadOfDepartment(int specialNumberPar) : base(specialNumberPar)
        { }

        public override string NameForXML()
        {
            return "HeadOfDepartment";
        }

        public override string ToString()
        {
            return "Head of Department";
        }
    }

    [Serializable]
    public class OfficeWorker : Employee
    {
        public OfficeWorker()
        { }

        public override string Position { get; set; } = "Office Worker";

        public OfficeWorker(int specialNumberPar) : base(specialNumberPar)
        { }

        public override string NameForXML()
        {
            return "OfficeWorker";
        }

        public override string ToString()
        {
            return "Office Worker";
        }
    }

    [Serializable]
    public class CleaningStaff : Employee
    {
        public CleaningStaff()
        { }

        public override string Position { get; set; } = "Cleaning Staff";

        public CleaningStaff(int specialNumberPar) : base(specialNumberPar)
        { }

        public override string NameForXML()
        {
            return "CleaningStaff";
        }

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
        public static bool NeedClear { get; set; } = true;
        private int SpecialNumberGenerator { get; set; } = 1;
        private bool AddEmployeeWasLastAction = false;


        private List<Employee> GetGroupOfEmployees<T>(int menuItemNumber, T employees, T abstractEmployees)
            where T : List<Employee>
        {
            List<Employee> employeesOfGroupToFind = new List<Employee>();

            for (int i = 0; i < employees.Count; i++)
                if (employees[i].Equals(abstractEmployees[menuItemNumber - (int)MenuItems.ShowHeadsOfDepartmentsListEnum]))
                    employeesOfGroupToFind.Add(employees[i]);
            return employeesOfGroupToFind;
        }

        public void ShowMenu(List<Employee> employees)
        {
            if (NeedClear)
            {
                Console.Clear();
                Console.WriteLine("1. Посмортреть список сотрудников\n2. Добавить сотрудника\n3. Удалить сотрудника\n4. Найти сотрудника\n5. Найти сотрудника в должности \"Head of Department\"\n6. Найти сотрудника в должности \"Office Worker\"\n7. Найти сотрудника в должности \"Cleaning Staff\"\n8. Сохранить список сотрудников в файл\n9. Загрузить список сотрудников из файла\n10. Выход\n"); //\n8. Особые свойства
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

        public enum MenuItems
        {
            ShowEmployeesListEnum = 1,
            AddEmployeeEnum,
            DeleteEmployeeEnum,
            FindEmployeeEnum,
            ShowHeadsOfDepartmentsListEnum,
            ShowOfficeWorkersListEnum,
            ShowCleaningStaffListEnum,
            SaveEmployeesListInFileEnum,
            LoadEmployeesListFromFileEnum,
            //SpecialPropertiesEnum,
            ExitEnum
        }

        public void ChooseMenuItem(int menuItemNumber, ref List<Employee> employees, List<Employee> abstractEmployees, ref bool repeatMain)
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

                case MenuItems.SaveEmployeesListInFileEnum:
                    //SerializationDeserialization.Serialize(employees, ListSaveAndLoadMaker.FileNameInput());
                    ListSaveAndLoadMaker listToSave = new ListSaveAndLoadMaker(employees);
                    listToSave.SaveList(listToSave, ListSaveAndLoadMaker.FileNameInput());
                    break;

                case MenuItems.LoadEmployeesListFromFileEnum:
                    //employees = SerializationDeserialization.Deserialize<List<Employee>>(employees, ListSaveAndLoadMaker.FileNameInput());
                    ListSaveAndLoadMaker listToLoad = new ListSaveAndLoadMaker();
                    employees = listToLoad.LoadList(employees, ListSaveAndLoadMaker.FileNameInput());
                    break;

                /*
                case MenuItems.SpecialPropertiesEnum:
                    TheInsAndOuts shower = new TheInsAndOuts();
                    shower.DemonstrationOfSpecialProperties();
                    break;
                */

                case MenuItems.ExitEnum:
                    repeatMain = false;
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
            Employee newEmployee = new Employee(SpecialNumberGenerator);
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

    /*
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
    */

    static class SerializationDeserialization
    {
        public static void Serialize<T>(T employeesToSave, string filePath)
        {
            Type[] types = new Type[] { typeof(HeadOfDepartment), typeof(OfficeWorker), typeof(CleaningStaff) };
            XmlSerializer xmlFormat = new XmlSerializer(typeof(List<Employee>), types);

            try
            {
                using (Stream serStream = new FileStream(filePath, FileMode.Create))
                {
                    xmlFormat.Serialize(serStream, employeesToSave);
                    Console.WriteLine("Список сотрудников успешно сохранен!\n");
                }
            }

            catch (Exception ex)
            {
                Console.WriteLine("Ошибка: " + ex.Message + "\n");
            }
        }

        public static T Deserialize<T>(T employees, string filePath)
        {
            Type[] types = new Type[] { typeof(HeadOfDepartment), typeof(OfficeWorker), typeof(CleaningStaff) };
            XmlSerializer xmlFormat = new XmlSerializer(typeof(List<Employee>), types);

            try
            {
                using (Stream deserStream = new FileStream(filePath, FileMode.Open))
                {
                    T loadedEmployees = (T)xmlFormat.Deserialize(deserStream);
                    Console.WriteLine("Список сотрудников успешно загружен!\n");
                    return loadedEmployees;
                }
            }

            catch (Exception ex)
            {
                Console.WriteLine("Ошибка: " + ex.Message + "\n");
                return employees;
            }
        }
    }


    class ListSaveAndLoadMaker
    {
        private List<Employee> employeesToSaveOrLoad = null;

        public ListSaveAndLoadMaker(List<Employee> employeesFromDataBase)
        {
            employeesToSaveOrLoad = employeesFromDataBase;
        }

        public ListSaveAndLoadMaker()
        { }

        public static string FileNameInput()
        {
            EmployeeDataBase.NeedClear = false;
            Console.Write("Введите имя файла: ");
            string fileName = Console.ReadLine();
            fileName = Regex.Replace(fileName, @"[\\/:*?""<>|]", "");
            if (!Regex.IsMatch(fileName, @".xml$"))
                fileName += ".xml";
            return fileName;
        }

        public void SaveList(ListSaveAndLoadMaker ListToSave, string filePath)
        {
            if (ListToSave.employeesToSaveOrLoad.Count > 0)
            {
                try
                {
                    using (FileStream saveStream = new FileStream(filePath, FileMode.Create))
                    {
                        XmlWriterSettings settings = new XmlWriterSettings();
                        settings.Indent = true;
                        XmlWriter writer = XmlWriter.Create(saveStream, settings);

                        writer.WriteStartElement("ArrayOfEmployee", "http://www.ipm.ifmo.ru");

                        foreach (Employee employee in ListToSave.employeesToSaveOrLoad)
                        {
                            employee.Name = Regex.Replace(employee.Name, @"[&<>'""]", "");
                            employee.LastName = Regex.Replace(employee.LastName, @"[&<>'""]", "");
                            employee.Patronymic = Regex.Replace(employee.Patronymic, @"[&<>'""]", "");
                            employee.BirthDate = Regex.Replace(employee.BirthDate, @"[&<>'""]", "");
                            employee.Position = Regex.Replace(employee.Position, @"[&<>'""]", "");

                            writer.WriteStartElement("Employee");
                            writer.WriteAttributeString("type", employee.NameForXML());

                            writer.WriteElementString("SpecialNumber", Convert.ToString(employee.SpecialNumber));
                            writer.WriteElementString("Name", employee.Name);
                            writer.WriteElementString("LastName", employee.LastName);
                            writer.WriteElementString("Patronymic", employee.Patronymic);
                            writer.WriteElementString("BirthDate", employee.BirthDate);
                            writer.WriteElementString("Position", employee.Position);

                            writer.WriteEndElement();
                        }

                        writer.WriteEndElement();

                        writer.Flush();
                        Console.WriteLine("Список сотрудников успешно сохранен!\n");
                    }
                }

                catch (Exception ex)
                {
                    Console.WriteLine("Ошибка: " + ex.Message + "\n");
                }
            }
            else
                Console.WriteLine("Список пуст. Сначала добавьте сотрудников.\n");
        }

        public List<Employee> LoadList(List<Employee> employees, string filePath)
        {
            List<Employee> ListToReturn = new List<Employee>();
            Employee tempEmp = new Employee();
            try
            {
                StringWriter stringWriter = new StringWriter();
                XmlTextWriter xmlTextWriter = new XmlTextWriter(stringWriter);

                XmlReaderSettings settings = new XmlReaderSettings();
                string xmlSchemePath = "forLoadingListFromXMLfile.xsd";
                settings.Schemas.Add("http://www.ipm.ifmo.ru", xmlSchemePath);
                settings.ValidationType = ValidationType.Schema;

                using (XmlReader reader = XmlReader.Create(filePath, settings))
                {
                    XmlDocument document = new XmlDocument();
                    document.Load(reader);
                    document.WriteTo(xmlTextWriter);
                    string validatedXmlDoc = Convert.ToString(stringWriter);

                    using (XmlReader readerFromValidFile = XmlReader.Create(new StringReader(validatedXmlDoc)))
                    {
                        int propertyNum = 0;
                        while (readerFromValidFile.Read())
                        {
                            switch (readerFromValidFile.NodeType)
                            {
                                case XmlNodeType.Element:
                                    switch (readerFromValidFile.Name)
                                    {
                                        case "SpecialNumber":
                                            propertyNum = 1;
                                            break;

                                        case "Name":
                                            propertyNum = 2;
                                            break;

                                        case "LastName":
                                            propertyNum = 3;
                                            break;

                                        case "Patronymic":
                                            propertyNum = 4;
                                            break;

                                        case "BirthDate":
                                            propertyNum = 5;
                                            break;

                                        case "Position":
                                            propertyNum = 6;
                                            break;
                                    }
                                    break;

                                case XmlNodeType.Text:
                                    switch (propertyNum)
                                    {
                                        case 1:
                                            tempEmp.SpecialNumber = Convert.ToInt32(readerFromValidFile.Value);
                                            break;

                                        case 2:
                                            tempEmp.Name = readerFromValidFile.Value;
                                            break;

                                        case 3:
                                            tempEmp.LastName = readerFromValidFile.Value;
                                            break;

                                        case 4:
                                            tempEmp.Patronymic = readerFromValidFile.Value;
                                            break;

                                        case 5:
                                            tempEmp.BirthDate = readerFromValidFile.Value;
                                            break;

                                        case 6:
                                            tempEmp.Position = readerFromValidFile.Value;
                                            break;
                                    }
                                    break;
                            }
                            if ((readerFromValidFile.NodeType == XmlNodeType.EndElement) && (readerFromValidFile.Name == "Employee"))
                            {
                                switch (tempEmp.Position)
                                {
                                    case "Head of Department":
                                        HeadOfDepartment newHoD = GetNewEmpDataToHoD(tempEmp);
                                        ListToReturn.Add(newHoD);
                                        break;

                                    case "Office Worker":
                                        OfficeWorker newOW = GetNewEmpDataToOW(tempEmp);
                                        ListToReturn.Add(newOW);
                                        break;

                                    case "Cleaning Staff":
                                        CleaningStaff newCS = GetNewEmpDataToCS(tempEmp);
                                        ListToReturn.Add(newCS);
                                        break;
                                }
                            }
                        }
                    }
                }
                Console.WriteLine("Список сотрудников успешно загружен!\n");
                return ListToReturn;
            }

            catch (XmlSchemaException ex)
            {
                Console.WriteLine("Ошибка в правильности XML-схемы: " + ex.Message + "\n");
                return employees;
            }

            catch (XmlException ex)
            {
                Console.WriteLine("XML-документ не соответствует XML-схеме: " + ex.Message + "\n");
                return employees;
            }

            catch (Exception ex)
            {
                Console.WriteLine("Ошибка: " + ex.Message + "\n");
                return employees;
            }
        }

        private HeadOfDepartment GetNewEmpDataToHoD(Employee tempEmp)
        {
            HeadOfDepartment temp = new HeadOfDepartment();
            temp.SpecialNumber = tempEmp.SpecialNumber;
            temp.Name = tempEmp.Name;
            temp.LastName = tempEmp.LastName;
            temp.Patronymic = tempEmp.Patronymic;
            temp.BirthDate = tempEmp.BirthDate;
            temp.Position = tempEmp.Position;
            return temp;
        }

        private OfficeWorker GetNewEmpDataToOW(Employee tempEmp)
        {
            OfficeWorker temp = new OfficeWorker();
            temp.SpecialNumber = tempEmp.SpecialNumber;
            temp.Name = tempEmp.Name;
            temp.LastName = tempEmp.LastName;
            temp.Patronymic = tempEmp.Patronymic;
            temp.BirthDate = tempEmp.BirthDate;
            temp.Position = tempEmp.Position;
            return temp;
        }

        private CleaningStaff GetNewEmpDataToCS(Employee tempEmp)
        {
            CleaningStaff temp = new CleaningStaff();
            temp.SpecialNumber = tempEmp.SpecialNumber;
            temp.Name = tempEmp.Name;
            temp.LastName = tempEmp.LastName;
            temp.Patronymic = tempEmp.Patronymic;
            temp.BirthDate = tempEmp.BirthDate;
            temp.Position = tempEmp.Position;
            return temp;
        }
    }
}