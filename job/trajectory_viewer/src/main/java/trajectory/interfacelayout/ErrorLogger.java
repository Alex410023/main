package trajectory.interfacelayout;

import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

/**
 * A utility class for logging errors to a file.
 */
public class ErrorLogger {
    private static final Logger logger = Logger.getLogger(ErrorLogger.class.getName());
    private static final String LOG_DIR = System.getProperty("java.io.tmpdir");

    static {
        try {
            FileHandler fh = new FileHandler(LOG_DIR + "/error.log", 10000, 1, true); // limit to 10KB per file
            logger.addHandler(fh);
            SimpleFormatter formatter = new SimpleFormatter();
            fh.setFormatter(formatter);
        } catch (SecurityException | IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Logs an error message to the error log file.
     *
     * @param message the error message to log
     */
    public static void logError(String message) {
        logger.severe(message);
    }
}