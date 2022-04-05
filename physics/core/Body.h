#ifndef BODY_H_INCLUDED
#define BODY_H_INCLUDED

#include <bits/stdc++.h>
#include "Point.h"
#include "../math/Vector.h"

namespace Physics{
    struct Body{
        private:
            std::vector<Point*> vertices;

        public:
            Body(){
                vertices = std::vector<Point*>();
            }

            ~Body(){
                for(Point* e : vertices)
                    delete e;
            }

            void AddVertex(Point* vertex){
                vertices.push_back(vertex);
            }

            void AddVertex(const PMath::Vector position){
                Point* vertex = new Point();
                vertex->position = position;

                vertices.push_back(vertex);
            }
    };
}

#endif // BODY_H_INCLUDED
