#include

static void do_demo(struct problem_spec *spec, double a, char *eps_filename) {
    struct mesh *mesh = make_mesh(spec, a);
    printf("vertices = %d, edges = %d, elems = %d\n",
            mesh->nnodes, mesh->nedges, mesh->nelems);

    mesh_to_eps(mesh, eps_filename);
    free_mesh(mesh);
}

//todo
static void show_usage(char *progname) {

}

int main(int argc) {

}
