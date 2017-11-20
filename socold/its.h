#ifndef __ITS_H
#define __ITS_H




typedef unsigned char       uint8_t;
class Phase
{
    public :
        Phase()
        {
            next_phID = 0;
        }
        ~Phase()
        {

        }
        uint8_t m_phID;
        void action()
        {
            //强制绿->红之间的过度黄灯
        }
//        string m_desc;
        uint8_t m_GS;
        uint8_t m_YT;
        uint8_t m_bindChannel;
    private:
        uint8_t next_phID;
};
class Plan
{
    public:
        uint8_t m_phID;
        uint8_t m_GT;
        uint8_t m_phSequence;
        Plan()
        {}
        void setplan(uint8_t _id,uint8_t _gt,uint8_t _se)
        {
            m_phID = _id;
            m_GT = _gt;
            m_phSequence = _se;
        }

};
class DP
{
    public:
//        uint8_t m_dpID;
        uint8_t m_DivTime;
        uint8_t m_plID;
        void action()
        {
            //抵达时间间隔时，发送切换信号量；
        }
        void setdp(uint8_t _div,uint8_t _plid)
        {
            m_DivTime = _div;
            m_plID = _plid;
        }
};



#endif
