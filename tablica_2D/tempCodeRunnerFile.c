ct {
	int r, c, v;
} triplet;

int read_sparse(triplet *triplet_array, int n_triplets) {
	int i;
	for (i = 0; i < n_triplets; i++) 
	{
		triplet *t = triplet_array+i;
		if (scanf("%d %d %d", &t->r, &t->c, &t->v) != 3) break;
	}
	return i;