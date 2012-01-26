#ifndef CBASEHANDLE_H
#define CBASEHANDLE_H

#include <cassert>

#define INVALID_HANDLE_REF 0x0
#define SERIAL_NB_BITS 16
//16 bits donc 2^16=65536 entité différente
#define INDEX_NB_BITS 16

//!Handle qui permet d'adresser dans le temps (serial) et dans la mémoire (index)
class CBaseHandle
{
    public:
		//!Contructeur invalide par défaut
        CBaseHandle() : m_handle(INVALID_HANDLE_REF) {}

		//!Construit le handle a partir de l'index/serial
        CBaseHandle(const unsigned int& index, const unsigned int& serial)
        {
			//Pas de overflow
            assert((index>>INDEX_NB_BITS)==0);
            assert((serial>>SERIAL_NB_BITS)==0);

			//fusionne l'index/serial
            m_handle = index | (serial << INDEX_NB_BITS);
        }

		//Construct from an int
		CBaseHandle(const int& handle) : m_handle(handle) {}

		//!Constructeur de copie
        CBaseHandle(const CBaseHandle& hHandle) : m_handle(hHandle.m_handle) {}

		//!Si le handle est initialisé
        bool isValid() const {return m_handle != INVALID_HANDLE_REF;}

		//!Retourne l'index
        unsigned int getIndex() const {
            return (m_handle << SERIAL_NB_BITS) >> SERIAL_NB_BITS;
        }

		//!Retourne la série
        unsigned int getSerial() const {
            return m_handle >> INDEX_NB_BITS;
        }

		//!Convertie le handle en entier non signé
        unsigned int toUInt() const {return m_handle;}

		//!Convertie le handle en entier
        operator unsigned int() const {return toUInt();}

		//!Assigne un handle à partir d'un autre
        CBaseHandle& operator=(const CBaseHandle& hHandle){
            m_handle=hHandle.m_handle;
            return *this;
        }

		//!Compare deux handle
        bool operator==(const CBaseHandle& hOther)
        {
            return m_handle == hOther;
        }

    private:
        unsigned int m_handle;
};

//!Structure qui permet de trier les handle par leur index
struct CHandleCmp{
    bool operator()(const CBaseHandle& hHandle1, const CBaseHandle& hHandle2) const
    {
        return hHandle1.getIndex() < hHandle2.getIndex();
    }
};

#endif // HW_CBASEHANDLE_H
