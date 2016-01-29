#ifndef OFFER_H_INCLUDED
#include <string>
#define OFFER_H_INCLUDED

enum OFFER_STATE {
    FREE = 0, RESERVED = 1, SOLD = 2
} ;

class Offer {
    private:
        std::string ownerUsername;
        std::string hotelName;
        std::string freeNum;
        std::string startDayOffer, startMonthOffer, startYearOffer;
        std::string endDayOffer, endMonthOffer, endYearOffer;
        std::string whoReserved = ""; // Jezeli nikt to empty
        OFFER_STATE offerState;
        float price;
    public:
        Offer(std::string ownerUsername,
        std::string hotelName,
        std::string freeNum,
        std::string startDayOffer, std::string startMonthOffer, std::string startYearOffer,
        std::string endDayOffer, std::string endMonthOffer, std::string endYearOffer,
        std::string whoReserved,
        OFFER_STATE offerState, float price){
            this->ownerUsername = ownerUsername;
            this->hotelName = hotelName;
            this->freeNum = freeNum;
            this->startDayOffer = startDayOffer;
            this->startMonthOffer = startMonthOffer;
            this->startYearOffer = startYearOffer;
            this->endDayOffer = endDayOffer;
            this->endMonthOffer = endMonthOffer;
            this->endYearOffer = endYearOffer;
            this->offerState = offerState;
            this->whoReserved = whoReserved;
            this->price = price;
        }
        std::string getWhoReserved(){
            return this->whoReserved;
        }
        std::string getOwnerUsername(){
            return this->ownerUsername;
        }
        OFFER_STATE getOfferState(){
            return this->offerState;
        }
        std::string getOfferStateString(){
            if(this->offerState == FREE){
                return "wolna";
            }else if(this->offerState == RESERVED){
                return "zarezerwowana";
            }else{
                return "sprzedana";
            }
        }
        void setOfferState(OFFER_STATE state){
            this->offerState = state;
        }
        std::string getHotelName(){
            return this->hotelName;
        }
        std::string getFreeNum(){
            return this->freeNum;
        }
        std::string getStartDayOffer(){
            return this->startDayOffer;
        }
        std::string getStartMonthOffer(){
            return this->startMonthOffer;
        }
        std::string getStartYearOffer(){
            return this->startYearOffer;
        }

        std::string getEndDayOffer(){
            return this->endDayOffer;
        }
        std::string getEndMonthOffer(){
            return this->endMonthOffer;
        }
        std::string getEndYearOffer(){
            return this->endYearOffer;
        }
        void setWhoReserved(std::string username){
            this->whoReserved = username;
        }
        float getPrice(){
            return this->price;
        }
        std::string toString(){
            std::string str;
            str.append(this->getOwnerUsername()).append(":");
            str.append(this->getHotelName()).append(":");
            str.append(this->getFreeNum()).append(":");
            str.append(this->getStartDayOffer()).append(":");
            str.append(this->getStartMonthOffer()).append(":");
            str.append(this->getStartYearOffer()).append(":");
            str.append(this->getEndDayOffer()).append(":");
            str.append(this->getEndMonthOffer()).append(":");
            str.append(this->getEndYearOffer()).append(":");
            str.append(this->getWhoReserved()).append(":");
            str.append(this->getOfferStateString());
            return str;
        }
};


#endif // OFFER_H_INCLUDED
