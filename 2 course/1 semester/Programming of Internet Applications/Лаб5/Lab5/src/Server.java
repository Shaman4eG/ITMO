import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server implements Runnable {
    private Socket socket;
    volatile static int i = 0;

    public Server(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        try (DataInputStream input = new DataInputStream(socket.getInputStream());
             DataOutputStream output = new DataOutputStream(socket.getOutputStream());)
        {
            while(true) {
                float x = input.readFloat();
                float y = input.readFloat();
                float r = input.readFloat();
                output.writeInt(InZoneChecker.containsPoint((int) x, (int) y, (int) r) ? 1 : 0);
            }
        } catch(Exception e) {
        }
    }


    public static void main(String[] args) {
        int portNumber = 8652;
        boolean listening = true;

        try (ServerSocket serverSocket = new ServerSocket(portNumber)) {
            while (listening) {
                new Thread(new Server(serverSocket.accept())).start();
            }
        } catch (IOException e) {
            System.err.println("Could not listen on port " + portNumber);
            System.exit(-1);
        }
    }
}

class InZoneChecker {
    public static boolean containsPoint(int x, int y, int r) {
        if (x < 0)
        {
            if ((x >= -r) && (y >= 0) && (y <= 0.5 * (x + r)))
                return true;
        }
        else if ((x <= r) && (y >= -0.5 * r) && (y <= Math.sqrt(Math.pow(r, 2) - Math.pow(x, 2))))
            return true;

        return  false;
    }
}
