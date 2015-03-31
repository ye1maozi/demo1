


#include "cocos2d.h"

// 鏃ュ織绾у埆锛屼篃鍙牴鎹嚜宸遍渶瑕佷慨鏀规坊鍔犵被鍒�
enum{
    LSLOG_VERBOSE = 0,
    LSLOG_DEBUG,
    LSLOG_INFO,
    LSLOG_WARN,
    LSLOG_ERROR,
    LSLOG_COUNT,
};

// 鎵撳嵃鏃ュ織绫诲埆鍓嶇紑
const std::string lsLog_name[LSLOG_COUNT] = {
        "(verbose)\t",
        "(debug)\t\t",
        "(info)\t\t",
        "(warn)\t\t",
        "(error)\t\t"
};

// 涓嶅悓绾у埆瀵瑰簲鐨� Android Jni 瀹炵幇鏂规硶鍚嶇О
const std::string lsLog_androidMethod[LSLOG_COUNT] = {
        "v",
        "d",
        "i",
        "w",
        "e"
};

/**
 @brief 鑷畾涔夋棩蹇楃郴缁燂紝鍓嶆湡浣跨敤锛屼互鍚庡彲浠ユ墿灞曚紭鍖�
 */
class LSLog: public cocos2d::CCObject {
public:
    /// verbose 璇︾粏鏃ュ織锛屼竴鑸父鐢ㄧ殑鎵撳嵃淇℃伅
    static void verbose(const char * pszFormat, ...);
    /// debug 璋冭瘯 ,璋冭瘯杩囩▼鎵�娉ㄦ剰鐨勪俊鎭�
    static void debug(const char * pszFormat, ...);
    /// info 涓�鑸俊鎭�,
    static void info(const char * pszFormat, ...);
    ///  warn 璀﹀憡淇℃伅
    static void warn(const char * pszFormat, ...);
    /// error 閿欒淇℃伅
    static void error(const char * pszFormat, ...);
private:
    // 闇�瑕佹樉绀虹殑鏃ュ織绾у埆瀹氫箟
    static const int LOG_VALUE;
    // 鎵撳嵃鏃ュ織鏂规硶
    static void printLog(int type, const char* format, va_list ap);
    // Android 骞冲彴鏃ュ織鎵撳嵃
    static void printAndroidLog(const char* methodName, const char* log);
};
