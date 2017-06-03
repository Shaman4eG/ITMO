public class Main {

    public static void main(String[] args)
    {
        if(args.length > 0)
            for (String arg: args)
                System.out.println(arg);
        else
            System.out.println("No arguments input.");

        int[] array = {3, 2, 1};
        java.util.Arrays.sort(array);

        for(int elem: array)
            System.out.println(elem);
    }
}
