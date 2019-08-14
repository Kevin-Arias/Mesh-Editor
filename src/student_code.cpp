#include "student_code.h"
#include "mutablePriorityQueue.h"

using namespace std;

namespace CGL
{

  double lerp(double point1, double point2, float t_value) {
      double total = (((1-t_value) * point1) + (t_value * point2));
      return total;
  }
  void BezierCurve::evaluateStep()
  {

    // TODO Part 1.
    // Perform one step of the Bezier curve's evaluation at t using de Casteljau's algorithm for subdivision.
    // Store all of the intermediate control points into the 2D vector evaluatedLevels.
    int level = (int)evaluatedLevels.size() - 1;
    if (evaluatedLevels[level].size() == 1) {
        return;
    }
    vector<Vector2D> new_step;
    for (int i = 0; i < evaluatedLevels[level].size() - 1; i++) {
        double lerpx = lerp(evaluatedLevels[level][i].x, evaluatedLevels[level][i+1].x, t);
        double lerpy = lerp(evaluatedLevels[level][i].y, evaluatedLevels[level][i+1].y, t);
        Vector2D lerped = Vector2D(lerpx, lerpy);
        new_step.push_back(lerped);
    }
    evaluatedLevels.push_back(new_step);
    return;
  }


  Vector3D BezierPatch::evaluate(double u, double v) const
  {
    // TODO Part 2.
    // Evaluate the Bezier surface at parameters (u, v) through 2D de Casteljau subdivision.
    // (i.e. Unlike Part 1 where we performed one subdivision level per call to evaluateStep, this function
    // should apply de Casteljau's algorithm until it computes the final, evaluated point on the surface)
    vector<Vector3D> lerped;
    for (int row = 0; row < 4; row++) {
        Vector3D u_lerped = evaluate1D(controlPoints[row], u);
        lerped.push_back(u_lerped);
    }
    return evaluate1D(lerped, v);
  }

  Vector3D BezierPatch::evaluate1D(std::vector<Vector3D> points, double t) const
  {
    // TODO Part 2.
    // Optional helper function that you might find useful to implement as an abstraction when implementing BezierPatch::evaluate.
    // Given an array of 4 points that lie on a single curve, evaluates the Bezier curve at parameter t using 1D de Casteljau subdivision.
    vector<Vector3D>first_round;
    for (int i = 0; i < 3; i++) {
        double first_x = lerp(points[i].x, points[i+1].x, t);
        double first_y = lerp(points[i].y, points[i+1].y, t);
        double first_z = lerp(points[i].z, points[i+1].z, t);
        Vector3D first = Vector3D(first_x,first_y,first_z);
        first_round.push_back(first);
    }

    vector<Vector3D>second_round;
    for (int i = 0; i < 2; i++) {
        double second_x = lerp(first_round[i].x, first_round[i+1].x, t);
        double second_y = lerp(first_round[i].y, first_round[i+1].y, t);
        double second_z = lerp(first_round[i].z, first_round[i+1].z, t);
        Vector3D second = Vector3D(second_x,second_y,second_z);
        second_round.push_back(second);
    }

    Vector3D third_round;
    for (int i = 0; i < 1; i++) {
        double third_x = lerp(second_round[i].x, second_round[i+1].x, t);
        double third_y = lerp(second_round[i].y, second_round[i+1].y, t);
        double third_z = lerp(second_round[i].z, second_round[i+1].z, t);
        third_round = Vector3D(third_x,third_y,third_z);
    }

    return third_round;
 }



  Vector3D Vertex::normal( void ) const
  {
    // TODO Part 3.
    // TODO Returns an approximate unit normal at this vertex, computed by
    // TODO taking the area-weighted average of the normals of neighboring
    // TODO triangles, then normalizing.

    Vector3D n = Vector3D(0,0,0);
    HalfedgeCIter h = halfedge();
    h = h->twin();
    HalfedgeCIter h_orig = h;
    do {
        Vector3D a = h->vertex()->position;
        h = h->next();
        Vector3D b = h->vertex()->position;
        h = h->twin();
        Vector3D c = h->vertex()->position;
        Vector3D ab_vector = b-a;
        Vector3D ac_vector = c-a;
        n += cross(ab_vector, ac_vector);

    } while (h != h_orig);
    return n.unit();

  }

  EdgeIter HalfedgeMesh::flipEdge( EdgeIter e0 )
  {
    // TODO Part 4.
    // TODO This method should flip the given edge and return an iterator to the flipped edge.
    if (e0->isBoundary()) {
        return e0;
    }

    HalfedgeIter b_h = e0->halfedge();
    HalfedgeIter c_h = b_h->next();
    HalfedgeIter a_h = c_h->next();
    HalfedgeIter c_t = b_h->twin();
    HalfedgeIter b_t = c_t->next();
    HalfedgeIter d_t = b_t->next();

    //Vertices
    VertexIter a = a_h->vertex();
    VertexIter b = b_h->vertex();
    VertexIter c = c_t->vertex();
    VertexIter d = d_t->vertex();

    //Faces
    FaceIter first_face = b_h->face();
    FaceIter second_face = c_t->face();

    //Begin performing flip
    a_h->setNeighbors(b_t, a_h->twin(), a, a_h->edge(), second_face);
    b_h->setNeighbors(d_t, c_t, a, e0, first_face);
    c_h->setNeighbors(b_h, c_h->twin(), c, c_h->edge(), first_face);
    b_t->setNeighbors(c_t, b_t->twin(), b, b_t->edge(), second_face);
    c_t->setNeighbors(a_h, b_h, d, e0, second_face);
    d_t->setNeighbors(c_h, d_t->twin(), d, d_t->edge(), first_face);
    first_face->halfedge() = b_h;
    second_face->halfedge() = c_t;
    a->halfedge() = a_h;
    b->halfedge() = b_t;
    c->halfedge() = c_h;
    d->halfedge() = c_t;


    return e0;
  }

  VertexIter HalfedgeMesh::splitEdge( EdgeIter e0 )
  {
    // TODO Part 5.
    // TODO This method should split the given edge and return an iterator to the newly inserted vertex.
    // TODO The halfedge of this vertex should point along the edge that was split, rather than the new edges.

    if (e0->isBoundary()) {
        return VertexIter();
    }

    HalfedgeIter b_h = e0->halfedge();
    HalfedgeIter c_h = b_h->next();
    HalfedgeIter a_h = c_h->next();
    HalfedgeIter c_t = b_h->twin();
    HalfedgeIter b_t = c_t->next();
    HalfedgeIter d_t = b_t->next();

    //Vertices
    VertexIter a = a_h->vertex();
    VertexIter b = b_h->vertex();
    VertexIter c = c_t->vertex();
    VertexIter d = d_t->vertex();

    //Faces
    FaceIter first = b_h->face();
    FaceIter second = c_t->face();


    //Initialize New Elements added during split
    HalfedgeIter m_to_a = newHalfedge();
    HalfedgeIter a_to_m = newHalfedge();
    HalfedgeIter m_to_d = newHalfedge();
    HalfedgeIter d_to_m = newHalfedge();
    HalfedgeIter m_to_b = newHalfedge();
    HalfedgeIter m_to_c = newHalfedge();
    EdgeIter edge_m_a = newEdge();
    EdgeIter edge_m_c = newEdge();
    EdgeIter edge_m_d = newEdge();
    FaceIter third = newFace();
    FaceIter fourth = newFace();


    //Begin incorporating m vertex
    VertexIter m = newVertex();
    Vector3D position = ((b->position) + (c->position)) * 0.5;
    m->position = position;

    //Begin Split
    b_h->setNeighbors(m_to_a, m_to_b, b, e0, first);
    c_h->setNeighbors(a_to_m, c_h->twin(), c, c_h->edge(), third);
    a_h->setNeighbors(b_h, a_h->twin(), a, a_h->edge(), first);
    c_t->setNeighbors(m_to_d, m_to_c, c, edge_m_c, second);
    b_t->setNeighbors(d_to_m, b_t->twin(), b, b_t->edge(), fourth);
    d_t->setNeighbors(c_t, d_t->twin(), d, d_t->edge(), second);
    m_to_a->setNeighbors(a_h, a_to_m, m, edge_m_a, first);
    a_to_m->setNeighbors(m_to_c, m_to_a, a, edge_m_a, third);
    m_to_d->setNeighbors(d_t, d_to_m, m, edge_m_d, second);
    d_to_m->setNeighbors(m_to_b, m_to_d, d, edge_m_d, fourth);
    m_to_b->setNeighbors(b_t, b_h, m, e0, fourth);
    m_to_c->setNeighbors(c_h, c_t, m, edge_m_c, third);
    a->halfedge() = a_h;
    b->halfedge() = b_h;
    c->halfedge() = c_h;
    d->halfedge() = d_t;
    m->halfedge() = m_to_c;
    e0->halfedge() = b_h;
    edge_m_a->halfedge() = a_to_m;
    edge_m_c->halfedge() = c_t;
    edge_m_d->halfedge() = d_to_m;
    first->halfedge() = b_h;
    second->halfedge() = c_t;
    third->halfedge() = a_to_m;
    fourth->halfedge() = d_to_m;

    return m;
  }



  void MeshResampler::upsample( HalfedgeMesh& mesh )
  {

    // TODO Part 6.
    // This routine should increase the number of triangles in the mesh using Loop subdivision.
    // Each vertex and edge of the original surface can be associated with a vertex in the new (subdivided) surface.
    // Therefore, our strategy for computing the subdivided vertex locations is to *first* compute the new positions
    // using the connectity of the original (coarse) mesh; navigating this mesh will be much easier than navigating
    // the new subdivided (fine) mesh, which has more elements to traverse. We will then assign vertex positions in
    // the new mesh based on the values we computed for the original mesh.


    // TODO Compute new positions for all the vertices in the input mesh, using the Loop subdivision rule,
    // TODO and store them in Vertex::newPosition. At this point, we also want to mark each vertex as being
    // TODO a vertex of the original mesh.

    for (VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++) {
        v->isNew = false;
        float n = (float) v->degree();
        float u;
        if (n==3.0f) {
            u = 3.0f/16.0f;
        } else {
            u = 3.0f/(8.0f*n);
        }
        Vector3D neighbor_position_sum = Vector3D(0,0,0);
        HalfedgeIter h = v->halfedge();
        HalfedgeIter start = h;
        do {
            VertexIter neighbor = h->twin()->vertex();
            neighbor_position_sum += neighbor->position;
            h = h->twin()->next();
        } while (start != h);

        v->newPosition = (1.0f - n * u) * (v->position) + u * neighbor_position_sum;
    }


    // TODO Next, compute the updated vertex positions associated with edges, and store it in Edge::newPosition.
    for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++) {
        e->isNew = false;
        HalfedgeIter a_halfedge = e->halfedge();
        HalfedgeIter b_halfedge = a_halfedge->twin();
        HalfedgeIter c_halfedge = b_halfedge->next()->next();
        HalfedgeIter d_halfedge = a_halfedge->next()->next();
        VertexIter a = a_halfedge->vertex();
        VertexIter b = b_halfedge->vertex();
        VertexIter c = c_halfedge->vertex();
        VertexIter d = d_halfedge->vertex();
        e->newPosition = (3.0f/8.0f) * ((a->position) + (b->position)) + (1.0f/8.0f) * ((c->position) + (d->position));
    }

    // TODO Next, we're going to split every edge in the mesh, in any order.  For future
    // TODO reference, we're also going to store some information about which subdivided
    // TODO edges come from splitting an edge in the original mesh, and which edges are new,
    // TODO by setting the flat Edge::isNew.  Note that in this loop, we only want to iterate
    // TODO over edges of the original mesh---otherwise, we'll end up splitting edges that we
    // TODO just split (and the loop will never end!)

    //Get last original mesh edge beofre splitting
    EdgeIter edge_before_split;
    for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++) {
        edge_before_split = e;
    }
    for (EdgeIter e = mesh.edgesBegin(); e != edge_before_split; e++) {
        VertexIter m = mesh.splitEdge(e);
        m->isNew = true;
        m->newPosition = e->newPosition;
        HalfedgeIter m_halfedge = m->halfedge();
        EdgeIter m_to_c = m_halfedge->edge();
        EdgeIter m_to_b = m_halfedge->twin()->next()->twin()->next()->edge();
        EdgeIter a_to_m = m_halfedge->next()->next()->edge();
        EdgeIter m_to_d = m_halfedge->twin()->next()->edge();
        m_to_c->isNew = false;
        m_to_b->isNew = false;
        a_to_m->isNew = true;
        m_to_d->isNew = true;
    }
    if(edge_before_split->isNew == false) {
        VertexIter m = mesh.splitEdge(edge_before_split);
        m->isNew = true;
        m->newPosition = edge_before_split->newPosition;
        HalfedgeIter m_halfedge = m->halfedge();
        EdgeIter m_to_c = m_halfedge->edge();
        EdgeIter m_to_b = m_halfedge->twin()->next()->twin()->next()->edge();
        EdgeIter a_to_m = m_halfedge->next()->next()->edge();
        EdgeIter m_to_d = m_halfedge->twin()->next()->edge();
        m_to_c->isNew = false;
        m_to_b->isNew = false;
        a_to_m->isNew = true;
        m_to_d->isNew = true;
    }


    // TODO Now flip any new edge that connects an old and new vertex.
    for (EdgeIter e = mesh.edgesBegin(); e != mesh.edgesEnd(); e++) {
        if (e->isNew == true) {
            HalfedgeIter first_halfedge = e->halfedge();
            HalfedgeIter second_halfedge = first_halfedge->twin();
            VertexIter first = first_halfedge->vertex();
            VertexIter second = second_halfedge->vertex();
            // Flip if one vertex is old and another is new
            if ((!first->isNew && second->isNew) || (first->isNew && !second->isNew)) {
                mesh.flipEdge(e);
            }
        }
    }


    // TODO Finally, copy the new vertex positions into final Vertex::position.
    for (VertexIter v = mesh.verticesBegin(); v != mesh.verticesEnd(); v++) {
        v->position = v->newPosition;
    }

    return;
  }
}
