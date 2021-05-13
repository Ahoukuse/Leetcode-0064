#include <iostream>
using namespace std;
class Solution {
private:

    // 标注状态
    enum Stat {
        /* 开始 */
        START = 0,
        SIGNED,
        NUMBER,
        DEC,
        DEC_NUM,
        /* 严格的小数,即要求一定至少要有一位数字 */
        SDEC,
        EXP,
        EXP_NUM,
        EXP_SIG,
        END
    };

    // 标注事件
    enum Event {
        EVENT_SPACE = 0,
        EVENT_NUM,
        EVENT_SIG,
        EVENT_DEC,
        EVENT_EXP,
        EVENT_INVALID
    };

    Stat table[10][6] = {
                //  空格   数字      符号     小数点     e   其他
    /* START    */ {START,NUMBER,  SIGNED,  SDEC,     END,END},
    /* SIGNED   */ {END,  NUMBER,  END,     SDEC,     END,END},
    /* NUMBER   */ {END,  NUMBER,  END,     DEC,      EXP,END},
    /* DEC      */ {END,  DEC_NUM, END,     END,      EXP,END},
    /* DEC_NUM  */ {END,  DEC_NUM, END,     END,      EXP,END},
    /* SDEC     */ {END,  DEC_NUM, END,     END,      END,END},
    /* EXP      */ {END,  EXP_NUM, EXP_SIG, END,      END,END},
    /* EXP_NUM  */ {END,  EXP_NUM, END,     END,      END,END},
    /* EXP_SIG  */ {END,  EXP_NUM, END,     END,      END,END},
    /* END      */ {END,  END,     END,     END,      END,END},
    };
    /// 判读输入c对应的事件
    /// \param c 输入的字符
    /// \return 返回对应字符c的事件
    Event get_event(const char c) {
        if (c == ' ')
            return EVENT_SPACE;
        else if (c == '+' || c == '-') {
            return EVENT_SIG;
        } else if (c == '.') {
            return EVENT_DEC;
        }
        else if (c >= '0' && c <= '9') {
            return EVENT_NUM;
        }
        else if (c == 'e' || c == 'E') {
            return EVENT_EXP;
        } else {
            return EVENT_INVALID;
        }
    }

public:

    bool isNumber(string s) {
        int len = s.size();
        Stat stat = START;
        int i = 0;
        for (; i < len && stat != END; ++i) {
            char c = s.at(i);
            Event event = get_event(c);
            stat = table[stat][event];
        }
        return i == len && (stat == NUMBER || stat == DEC_NUM || stat == EXP_NUM || stat == DEC);
    }
};


int main() {
    string testCases[] = {
            "", " ",
            "  -2.3","2.3","+2 .3",
            "1234","-234","+2e4",
            "1234","-234","+2e4e",
            "+2E34","-.2E34",
            "+2E+2","-.2E-4","-.2E-4.",
            "1.","-5.e","-6E6.",
            ".1",".3E+3",".1E.5",
            "++1","abc","45.7e9",
            ".",".1",".e3","1.E3"
    };
    Solution solution;
    for (const string& s: testCases) {
        cout<<"\""<< s << "\"" <<" is "<<(solution.isNumber(s) ? "valid":"invalid") << endl;
    }
    return 0;
}
