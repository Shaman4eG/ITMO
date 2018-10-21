namespace SWT.Lab1
{
    static class ConstantsForTesting
    {
        public static readonly string ChromeExeDirectory = @"C:\Repositories\ITMO\3 course\2 semester\SWT\Common";

        public static readonly string WebsiteUrl = "https://www.tumblr.com/";
        public static readonly string Email = "etoktotakoy@mail.ru";
        public static readonly string Password = "somerandompassword";

        public static readonly string LoginButtonPath = "//button[@id='signup_login_button']";
        public static readonly string EmailTextFieldPath = "//input[@id='signup_determine_email']";
        public static readonly string SubmitButtonPath = "//button[@id='signup_forms_submit']";
        public static readonly string UsePasswordButtonPath = "(//div[@id='signup_magiclink']/child::node())[2]/a";
        public static readonly string PasswordTextFieldPath = "//input[@id='signup_password']";

    }
}
