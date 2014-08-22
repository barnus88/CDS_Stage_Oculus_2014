#ifndef STAR_H
#define STAR_H


class Star
{
    public:
        Star(int id, double mass, float x, float y, float z, double age);
        virtual ~Star();
        double m_age, m_mass, m_x, m_y, m_z, m_posX, m_posY,m_posZ;
        int m_id;
    protected:
    private:



};

#endif // STAR_H
