package pop3.server.state;

import pop3.server.Pop3Session;
import pop3.server.SampleDataBase;

import java.util.ArrayList;
import java.util.Collections;

public class TransactionState extends Pop3SessionState {
    private final ArrayList<Integer> deletions;

    public TransactionState(Pop3Session session) {
        super(session);
        this.deletions = new ArrayList<Integer>();
    }

    @Override
    public void capa(String[] arguments) {
        super.session.sendPositive("");
        super.session.sendResponse("USER");
        super.session.sendResponse("PASS");
        super.session.sendResponse("STAT");
        super.session.sendResponse("LIST");
        super.session.sendResponse("RETR");
        super.session.sendResponse("DELE");
        super.session.sendResponse("NOOP");
        super.session.sendResponse("RSET");
        super.session.sendResponse("QUIT");
        super.session.sendResponse(".");
    }

    @Override
    public void user(String[] arguments) {
        super.session.sendNegative();
    }

    @Override
    public void pass(String[] arguments) {
        super.session.sendNegative();
    }

    @Override
    public void stat(String[] arguments) {
        super.session.sendPositive(String.valueOf(SampleDataBase.messages.size()));
    }

    @Override
    public void list(String[] arguments) {
        super.session.sendPositive();
        var counter = 0;
        for (var message : SampleDataBase.messages) {
            super.session.sendResponse(counter + " " + message.length());
            counter += 1;
        }
        super.session.sendResponse(".");
    }

    @Override
    public void retr(String[] arguments) {
        var message = SampleDataBase.messages.get(Integer.valueOf(arguments[1]));
        super.session.sendPositive();
        var counter = 0;
        while (counter < (message.length() - 510)) {
            super.session.sendResponse(message.substring(counter, counter + 510));
            counter += 510;
        }
        super.session.sendResponse(message.substring(counter));
        super.session.sendResponse(".");
    }

    @Override
    public void dele(String[] arguments) {
        this.deletions.add(Integer.valueOf(arguments[1]));
        super.session.sendPositive();
    }

    @Override
    public void noop(String[] arguments) {
        super.session.sendPositive();
    }

    @Override
    public void rset(String[] arguments) {
        this.deletions.clear();
        super.session.sendPositive();
    }

    @Override
    public void quit(String[] arguments) {
        // Perform updates:
        Collections.sort(this.deletions);
        Collections.reverse(this.deletions);
        for (var deletion : this.deletions) {
            SampleDataBase.messages.remove(deletion.intValue());
        }
        // Close socket:
        super.session.close();
    }
}