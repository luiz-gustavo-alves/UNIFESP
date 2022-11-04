public class TrafficController {

    private boolean bridgeBlocked = false;

    private synchronized void leaveBridge() {
        bridgeBlocked = false;
        notifyAll();
    }

    private synchronized void enterBridge() {

        while (bridgeBlocked) {
            try {
                wait();
            } catch(InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        bridgeBlocked = true;
        notifyAll();
    }

    public void enterLeft() {
        enterBridge();
    }

    public void enterRight() {
        enterBridge();
    }

    public void leaveLeft() {
        leaveBridge();
    }

    public void leaveRight() {
        leaveBridge();
    }
}