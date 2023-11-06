package pop3.server;

import javax.net.ServerSocketFactory;
import java.io.IOException;
import java.net.ServerSocket;

public class Pop3Server {
    ServerSocket serverSocket;

    public void open() {
        try {
            this.serverSocket = ServerSocketFactory.getDefault().createServerSocket(110);
            while (true) {
                Pop3Session session = new Pop3Session(serverSocket.accept());
                new Thread(session).start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (serverSocket != null) {
                try {
                    serverSocket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}