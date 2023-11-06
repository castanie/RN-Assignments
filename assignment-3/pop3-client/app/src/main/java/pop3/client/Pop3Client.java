package pop3.client;

import javax.net.ssl.SSLSocketFactory;
import java.io.*;
import java.net.Socket;

public class Pop3Client implements AutoCloseable {
    private Socket clientSocket;
    private BufferedReader inputReader;
    private BufferedWriter outputWriter;

    public void open(String host, Integer port) throws IOException {
        this.clientSocket = SSLSocketFactory.getDefault().createSocket(host, port);
        this.inputReader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
        this.outputWriter = new BufferedWriter(new OutputStreamWriter(clientSocket.getOutputStream()));
    }

    @Override
    public void close() throws IOException {
        this.inputReader.close();
        this.outputWriter.close();
        this.clientSocket.close();
    }

    public void sendCommand(String message) {
        try {
            this.outputWriter.write(message + "\r\n");
            this.outputWriter.flush();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void readSingleLineResponse() {
        try {
            String response = this.inputReader.readLine();
            System.out.println(response);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    private void readMultiLineResponse() {
        try {
            var response = this.inputReader.readLine();
            System.out.println(response);
            if (response.startsWith("-ERR")) {
                return;
            }
            while (!(response = this.inputReader.readLine()).equals(".")) {
                System.out.println(response);
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Arguments: none
     * <p>
     * Restrictions:
     * may only be given in the TRANSACTION state
     * <p>
     * Discussion:
     * The POP3 server issues a positive response with a line
     * containing information for the maildrop. This line is
     * called a "drop listing" for that maildrop.
     * <p>
     * In order to simplify parsing, all POP3 servers are
     * required to use a certain format for drop listings. The
     * positive response consists of "+OK" followed by a single
     * space, the number of messages in the maildrop, a single
     * space, and the size of the maildrop in octets. This memo
     * makes no requirement on what follows the maildrop size.
     * Minimal implementations should just end that line of the
     * response with a CRLF pair. More advanced implementations
     * may include other information.
     */
    public void stat() {
        sendCommand("STAT");
        readSingleLineResponse();
    }

    /**
     * Arguments:
     * a message-number (optional), which, if present, may NOT
     * refer to a message marked as deleted
     * <p>
     * Restrictions:
     * may only be given in the TRANSACTION state
     * <p>
     * Discussion:
     * If an argument was given and the POP3 server issues a
     * positive response with a line containing information for
     * that message. This line is called a "scan listing" for
     * that message.
     * <p>
     * If no argument was given and the POP3 server issues a
     * positive response, then the response given is multi-line.
     * After the initial +OK, for each message in the maildrop,
     * the POP3 server responds with a line containing
     * information for that message. This line is also called a
     * "scan listing" for that message. If there are no
     * messages in the maildrop, then the POP3 server responds
     * with no scan listings--it issues a positive response
     * followed by a line containing a termination octet and a
     * CRLF pair.
     * <p>
     * In order to simplify parsing, all POP3 servers are
     * required to use a certain format for scan listings. A
     * scan listing consists of the message-number of the
     * message, followed by a single space and the exact size of
     * the message in octets. Methods for calculating the exact
     * size of the message are described in the "Message Format"
     * section below. This memo makes no requirement on what
     * follows the message size in the scan listing. Minimal
     * implementations should just end that line of the response
     * with a CRLF pair. More advanced implementations may
     * include other information, as parsed from the message.
     */
    public void list() {
        sendCommand("LIST");
        readMultiLineResponse();
    }

    public void list(int number) {
        sendCommand("LIST " + number);
        readSingleLineResponse();
    }

    /**
     * Arguments:
     * a message-number (required) which may NOT refer to a
     * message marked as deleted
     * <p>
     * Restrictions:
     * may only be given in the TRANSACTION state
     * <p>
     * Discussion:
     * If the POP3 server issues a positive response, then the
     * response given is multi-line. After the initial +OK, the
     * POP3 server sends the message corresponding to the given
     * message-number, being careful to byte-stuff the termination
     * character (as with all multi-line responses).
     */
    public void retr(int number) {
        sendCommand("RETR " + number);
        readMultiLineResponse();
    }

    /**
     * Arguments:
     * a message-number (required) which may NOT refer to a
     * message marked as deleted
     * <p>
     * Restrictions:
     * may only be given in the TRANSACTION state
     * <p>
     * Discussion:
     * The POP3 server marks the message as deleted. Any future
     * reference to the message-number associated with the message
     * in a POP3 command generates an error. The POP3 server does
     * not actually delete the message until the POP3 session
     * enters the UPDATE state.
     */
    public void dele(int number) {
        sendCommand("DELE " + number);
        readSingleLineResponse();
    }

    /**
     * Arguments: none
     * <p>
     * Restrictions:
     * may only be given in the TRANSACTION state
     * <p>
     * Discussion:
     * The POP3 server does nothing, it merely replies with a
     * positive response.
     */
    public void noop() {
        sendCommand("NOOP");
        readSingleLineResponse();
    }

    /**
     * Arguments: none
     * <p>
     * Restrictions:
     * may only be given in the TRANSACTION state
     * <p>
     * Discussion:
     * If any messages have been marked as deleted by the POP3
     * server, they are unmarked. The POP3 server then replies
     * with a positive response.
     */
    public void rset() {
        sendCommand("RSET");
        readSingleLineResponse();
    }

    /**
     * Arguments:
     * a string identifying a mailbox (required), which is of
     * significance ONLY to the server
     * <p>
     * Restrictions:
     * may only be given in the AUTHORIZATION state after the POP3
     * greeting or after an unsuccessful USER or PASS command
     * <p>
     * Discussion:
     * To authenticate using the USER and PASS command
     * combination, the client must first issue the USER
     * command. If the POP3 server responds with a positive
     * status indicator ("+OK"), then the client may issue
     * either the PASS command to complete the authentication,
     * or the QUIT command to terminate the POP3 session. If
     * the POP3 server responds with a negative status indicator
     * ("-ERR") to the USER command, then the client may either
     * issue a new authentication command or may issue the QUIT
     * command.
     * <p>
     * The server may return a positive response even though no
     * such mailbox exists. The server may return a negative
     * response if mailbox exists, but does not permit plaintext
     * password authentication.
     */
    public void user(String username) {
        sendCommand("USER " + username);
        readSingleLineResponse();
    }

    /**
     * Arguments:
     * a server/mailbox-specific password (required)
     * <p>
     * Restrictions:
     * may only be given in the AUTHORIZATION state immediately
     * after a successful USER command
     * <p>
     * Discussion:
     * When the client issues the PASS command, the POP3 server
     * uses the argument pair from the USER and PASS commands to
     * determine if the client should be given access to the
     * appropriate maildrop.
     * <p>
     * Since the PASS command has exactly one argument, a POP3
     * server may treat spaces in the argument as part of the
     * password, instead of as argument separators.
     */
    public void pass(String password) {
        sendCommand("PASS " + password);
        readSingleLineResponse();
    }

    /**
     * Arguments: none
     * <p>
     * Restrictions: none
     * <p>
     * Discussion:
     * The POP3 server removes all messages marked as deleted
     * from the maildrop and replies as to the status of this
     * operation. If there is an error, such as a resource
     * shortage, encountered while removing messages, the
     * maildrop may result in having some or none of the messages
     * marked as deleted be removed. In no case may the server
     * remove any messages not marked as deleted.
     * <p>
     * Whether the removal was successful or not, the server
     * then releases any exclusive-access lock on the maildrop
     * and closes the TCP connection.
     */
    public void quit() {
        sendCommand("QUIT");
        readSingleLineResponse();
    }
}
