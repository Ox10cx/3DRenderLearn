package com.gx.kotlin.scene.log;

import android.util.Log;

import androidx.annotation.IntDef;

import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;

public final class Logger {

    private static final LoggerDefinition DEFAULT = new LoggerDefinition() {

        @Override
        public void v(String tag, String msg) {
            Log.v(tag, msg);
        }

        @Override
        public void v(String tag, String msg, Throwable tr) {
            Log.v(tag, msg, tr);
        }

        @Override
        public void d(String tag, String msg) {
            Log.d(tag, msg);
        }

        @Override
        public void d(String tag, String msg, Throwable tr) {
            Log.d(tag, msg, tr);
        }

        @Override
        public void i(String tag, String msg) {
            Log.i(tag, msg);
        }

        @Override
        public void i(String tag, String msg, Throwable tr) {
            Log.i(tag, msg, tr);
        }

        @Override
        public void w(String tag, String msg) {
            Log.w(tag, msg);
        }

        @Override
        public void w(String tag, String msg, Throwable tr) {
            Log.w(tag, msg, tr);
        }

        @Override
        public void e(String tag, String msg) {
            Log.e(tag, msg);
        }

        @Override
        public void e(String tag, String msg, Throwable tr) {
            Log.e(tag, msg, tr);
        }
    };

    private static volatile LoggerDefinition logger = DEFAULT;

    @LogLevel
    private static int logLevel;

    public static void setVerbosity(@LogLevel int logLevel) {
        Logger.logLevel = logLevel;
    }


    public static void setLoggerDefinition(LoggerDefinition loggerDefinition) {
        logger = loggerDefinition;
    }


    public static void v(String tag, String msg) {
        if (logLevel <= VERBOSE) {
            logger.v(tag, msg);
        }
    }

    public static void v(String tag, String msg, Throwable tr) {
        if (logLevel <= VERBOSE) {
            logger.v(tag, msg, tr);
        }
    }

    public static void d(String tag, String msg) {
        if (logLevel <= DEBUG) {
            logger.d(tag, msg);
        }
    }

    public static void d(String tag, String msg, Throwable tr) {
        if (logLevel <= DEBUG) {
            logger.d(tag, msg, tr);
        }
    }


    public static void i(String tag, String msg) {
        if (logLevel <= INFO) {
            logger.i(tag, msg);
        }
    }


    public static void i(String tag, String msg, Throwable tr) {
        if (logLevel <= INFO) {
            logger.i(tag, msg, tr);
        }
    }


    public static void w(String tag, String msg) {
        if (logLevel <= WARN) {
            logger.w(tag, msg);
        }
    }


    public static void w(String tag, String msg, Throwable tr) {
        if (logLevel <= WARN) {
            logger.w(tag, msg, tr);
        }
    }


    public static void e(String tag, String msg) {
        if (logLevel <= ERROR) {
            logger.e(tag, msg);
        }
    }


    public static void e(String tag, String msg, Throwable tr) {
        if (logLevel <= ERROR) {
            logger.e(tag, msg, tr);
        }
    }

    public static void log(int severity, String tag, String message) {
        switch (severity) {
            case Log.VERBOSE:
                Logger.v(tag, message);
                break;
            case Log.DEBUG:
                Logger.d(tag, message);
                break;
            case Log.INFO:
                Logger.i(tag, message);
                break;
            case Log.WARN:
                Logger.w(tag, message);
                break;
            case Log.ERROR:
                Logger.e(tag, message);
                break;
            default:
                throw new UnsupportedOperationException();
        }
    }


    public static final int VERBOSE = Log.VERBOSE;


    public static final int DEBUG = Log.DEBUG;


    public static final int INFO = Log.INFO;


    public static final int WARN = Log.WARN;


    public static final int ERROR = Log.ERROR;


    public static final int NONE = 99;


    @IntDef( {VERBOSE, DEBUG, INFO, WARN, ERROR, NONE})
    @Retention(RetentionPolicy.SOURCE)
    public @interface LogLevel {
    }
}
