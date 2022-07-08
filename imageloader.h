#pragma once //membaca file dengan format Woman1.nfg
#include <math.h>

class _Vec2 {
public:
	GLfloat x;
	GLfloat y;
};

class _Vec3 {
public:
	GLfloat x;
	GLfloat y;
	GLfloat z;
};

class _VecInt3 {
public:
	GLint x;
	GLint y;
	GLint z;
};

class loaderNfg {

	struct vertex {
		_Vec3 pos, norm, binorm, tgt;
		_Vec2 uv;
	};

	struct pattern {
		_VecInt3 pos;
	};

public:
	struct vertex JumlahVertex[512];
	struct pattern JumlahTampilan[718];
	GLint totalNrVertex, totalNFG;

private:
	FILE* loadModel;

	float px, py, pz, nx, ny, nz, bx, by, bz, tx, ty, tz, u, v;
	int x, y, z;
	char junk[200];

	bool loadFile() {
		fopen_s(&loadModel, "J:/672020028/672020028/Woman1.nfg", "r");
		if (!loadModel) {
			return false;
		}
		return true;
	}

	void loadNrVertex() {
		// Mendapatkan total node
		fscanf_s(this->loadModel, "NrVertices : %d", &totalNrVertex);
	}

	void loadCoordinate() {
		for (int i = 0; i < totalNrVertex; i++) {
			// Membaca nilai pada setiap baris 
			fscanf_s(loadModel, "%*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];", &px, &py, &pz, &nx, &ny, &nz, &bx, &by, &bz, &tx, &ty, &tz, &u, &v);

			this->JumlahVertex[i].pos.x = px;
			this->JumlahVertex[i].pos.y = py;
			this->JumlahVertex[i].pos.z = pz;

			this->JumlahVertex[i].norm.x = nx;
			this->JumlahVertex[i].norm.y = ny;
			this->JumlahVertex[i].norm.z = nz;

			this->JumlahVertex[i].binorm.x = bx;
			this->JumlahVertex[i].binorm.y = by;
			this->JumlahVertex[i].binorm.z = bz;

			this->JumlahVertex[i].tgt.x = tx;
			this->JumlahVertex[i].tgt.y = ty;
			this->JumlahVertex[i].tgt.z = tz;

			this->JumlahVertex[i].uv.x = u;
			this->JumlahVertex[i].uv.y = v;
		}
	}

	void loadNrIndices() {
		fscanf_s(this->loadModel, "\nNrIndices:%d", &totalNFG);
	}

	void trianglePattern() {

		int jumTampilan = totalNFG / 3;

		fscanf_s(this->loadModel, "\n");

		for (int i = 0; i < jumTampilan; i++) {
			fscanf_s(this->loadModel, "%*d. %d, %d, %d", &x, &y, &z);
			this->JumlahTampilan[i].pos.x = x;
			this->JumlahTampilan[i].pos.y = y;
			this->JumlahTampilan[i].pos.z = z;
		}

	}

	void closeFile() {
		fclose(loadModel);
	}

public:
	void readfile() {
		if (this->loadFile()) {
			this->loadNrVertex();
			this->loadCoordinate();
			this->loadNrIndices();
			this->trianglePattern();
			this->closeFile();
		}
		else {
			printf("File Tidak Bisa Di Proses");
		}
	}
};