#ifndef VIBRANT_SAMPLE_SINGLETONTEST_H
#define VIBRANT_SAMPLE_SINGLETONTEST_H

#include "vsingleton.h"

using namespace Vibrant;

/** 
 * @brief Sample singleton class.
 * 
 * @author Chris Culy
 */
class SingletonTest : public Singleton< SingletonTest >
{
    public:
        
        /**
         * @brief Constructor.
         * 
         * @param x The x variable.
         * @param y The y variable.
         * @param z The z variable.
         */
        SingletonTest ( int x, int y, int z )
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        /**
         * @brief Destructor.
         */
        ~SingletonTest ()
        {
        }
        
        /**
         * @brief Retrieves the x variable.
         * 
         * @return The x variable.
         */
        int GetX ()
        {
            return x;
        }
        
        /**
         * @brief Retrieves the y variable.
         * 
         * @return The y variable.
         */
        int GetY ()
        {
            return y;
        }
        
        /**
         * @brief Retrieves the z variable.
         * 
         * @return The z variable.
         */
        int GetZ ()
        {
            return z;
        }
        
    private:
        
        /** @brief Holds the x variable. */
        int x;

        /** @brief Holds the y variable. */
        int y;

        /** @brief Holds the z variable. */
        int z;
};

#endif
