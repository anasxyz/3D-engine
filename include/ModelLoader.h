#pragma once

#include "Mesh.h"

#include <stdexcept>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

class ModelLoader {
public:
  static Mesh loadMesh(const std::string &path) {
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_GenNormals |
                  aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    if (!scene || !scene->mRootNode || scene->mNumMeshes == 0) {
      throw std::runtime_error("Failed to load model: " + path);
    }

    aiMesh *aMesh = scene->mMeshes[0];

    std::vector<GLfloat> positions;
    std::vector<GLfloat> colors;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texCoords;
    std::vector<GLuint> indices;

    for (unsigned i = 0; i < aMesh->mNumVertices; i++) {
      positions.push_back(aMesh->mVertices[i].x);
      positions.push_back(aMesh->mVertices[i].y);
      positions.push_back(aMesh->mVertices[i].z);
      positions.push_back(1.0f);

      if (aMesh->HasNormals()) {
        normals.push_back(aMesh->mNormals[i].x);
        normals.push_back(aMesh->mNormals[i].y);
        normals.push_back(aMesh->mNormals[i].z);
      }

      if (aMesh->HasTextureCoords(0)) {
        texCoords.push_back(aMesh->mTextureCoords[0][i].x);
        texCoords.push_back(aMesh->mTextureCoords[0][i].y);
      } else {
        texCoords.push_back(0.0f);
        texCoords.push_back(0.0f);
      }

      // default color = white
      colors.push_back(1.0f);
      colors.push_back(1.0f);
      colors.push_back(1.0f);
      colors.push_back(1.0f);
    }

    for (unsigned i = 0; i < aMesh->mNumFaces; i++) {
      const aiFace &face = aMesh->mFaces[i];
      indices.push_back(face.mIndices[0]);
      indices.push_back(face.mIndices[1]);
      indices.push_back(face.mIndices[2]);
    }

    Mesh mesh;
    mesh.setup(positions, colors, normals, indices, &texCoords);
    return mesh;
  }
};
