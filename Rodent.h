#ifndef RODENT_H
#define RODENT_H

enum RodentType {MALE_MOUSE, FEMALE_MOUSE};

// forward declaration
class World;

class Rodent {
    public:

        Rodent() { infected = false; immune = false; };

        // Create a rodent at the given coordinates.
        Rodent(World* aWorld, int xcoord, int ycoord);
        virtual ~Rodent() { }

        // In the given world moves this rodent.
        virtual void move() = 0;

        // Makes this rodent breed.
        virtual void breed() = 0;

        // Returns the type of this rodent.
        virtual RodentType getType() const = 0;

        // Flags this rodent as moved or not.
        void setMoved(bool hasMoved);

        // The character representation of this rodent.
        virtual char representation() const = 0;

        // The size of this rodent.
        virtual int size() const = 0;

        // Has this rodent moved in this time slot or not?
        bool hasMoved() const;

        // Returns true if rodent is dead, false otherwise.
        virtual bool isDead() const;
    
        bool in_range(int xx, int yy);
        
        bool infected; // Creates bool variable to check if rodent is infected
        bool immune; // Creates bool variable to check if rodent is immune to infection
        bool adult; // Creates bool variable to check if rodent is adult
        int infectedDeathTick; // Creates int variable for infection death counter
    
    protected:
        // Generates an offspring at the given position.
        virtual void generateOffspring(int whereX, int whereY) = 0;

        // Moves this rodent from coordinates (x,y) to (xNew,yNew).
        void movesTo(int xNew, int yNew);

        // Breeds a new rodent at an adjacent cell. Tries to produce one new
        // rodent in UP, DOWN, LEFT, or RIGHT cell (in that order).  Makes
        // sure not to breed off the grid.
        void breedAtAdjacentCell();

        // This rodent's x position in the world.
        int x;

        // This rodent's y position in the world.
        int y;

        // Has moved this turn?
        bool moved;

        // Number of ticks since breeding.
        int breedTicks;

        // A pointer to the world in which this rodent lives.
        World* world;
    private:
};

#endif // RODENT_H
