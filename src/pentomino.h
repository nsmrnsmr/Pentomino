#ifndef PENTOMINO_2021_12_14
#define PENTOMINO_2021_12_14

#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Eigen/Core"
#define PI 3.141592653589793

struct Pentomino{
  using MatXi = Eigen::MatrixXi;
  using Mat2i = Eigen::Matrix2i;
  using Vec2i = Eigen::Vector2i;

  std::vector<Vec2i> coords; //ピースの相対座標
  int pattern; //ピースのパターン数（回転させたり）
  int color; //ピースの色

  int counter; //何パターンのピースまで調べたか
  bool use; //そのピースを使ったか

  int sp; //特殊なピースにタグ付け


  Pentomino(int n=1, int col=47, int s=0):
    pattern(n),
    color(col),
    counter(0),
    use(false),
    sp(s)
  {
    coords.resize(5);
  }

  //spをセット
  void setSP(int s){
    sp = s;
  }

  //相対座標をセット
  void setCoord(int i, const Vec2i &p){
    coords[i] = p;
  }

  void setCoord(int i, int x, int y){
    coords[i].x() = x;
    coords[i].y() = y;
  }

  //相対座標たちをセット
  void setCoords(const std::vector<Vec2i> &p){
    for(int i=0; i<5; i++){
      coords[i] = p[i];
    }
  }

  //ピースのパターン数をセット
  void setPattern(int n){
    pattern = n;
  }

  //ピースの色をセット
  void setColor(int col){
    color = col;
  }

  //ピースの相対座標を返す
  std::vector<Vec2i> getCoords(){
    std::vector<Vec2i> p(5);
    p = pop(counter);
    counter++;
    return p;
  }

  //nパターン目のペントミノの相対座標を返す
  std::vector<Vec2i> pop(int n){
    //std::cout <<"n: "<< n <<"\n";
    std::vector<Vec2i> p(5);
    if(sp == 1){
      if(n < pattern/2){
        p = rotate(n);
      }else{
        p = symmetric(n);
      }
    }else if(sp == 2){
      p = rotate(n);
    }else{
      if(pattern == 2 || pattern == 4 || n < pattern/2 ){
        p = rotate(n);
      }else{
        p = symmetric(n);
      }
    }
    return p;
  }

private:
  //対称移動＋回転させる
  std::vector<Vec2i> symmetric(int n){
    //対称移動
    Mat2i s;
    s << -1, 0, 0, 1;
    std::vector<Vec2i> p(5);
    for(int i=0; i<5; i++){
      p[i] = s * coords[i];
    }
    if( n != 0 ){
      //回転
      Mat2i r;
      r << (int)std::cos(n*PI/2), -1*(int)std::sin(n*PI/2),
           (int)std::sin(n*PI/2), (int)std::cos(n*PI/2);
      for(int i=0; i<5; i++){
        p[i] = r * p[i];
      }
    }
    auto c =  [](const Vec2i &a, const Vec2i &b){
                  if( a.x() == b.x() ) return a.y() < b.y();
                  else return a.x() < b.x();};
    std::sort(p.begin(), p.end(), c);
   // std::cout << "min coord "<< p[0] <<"\n";
    for(int i=1; i<5; i++){
    //  std::cout << "other "<< p[i] <<"\n";
      p[i] -= p[0];
    }
    p[0] << 0, 0;
    return p;
  }

  //回転させる
  std::vector<Vec2i> rotate(int n){
    if( n == 0 ) return coords;
    Mat2i r;
    r << (int)std::cos(n*PI/2), -1*(int)std::sin(n*PI/2),
         (int)std::sin(n*PI/2), (int)std::cos(n*PI/2);
    std::vector<Vec2i> p(5);
    for(int i=0; i<5; i++){
      p[i] = r * coords[i];
    }
    auto c =  [](const Vec2i &a, const Vec2i &b){
                  if( a.x() == b.x() ) return a.y() < b.y();
                  else return a.x() < b.x();};
    std::sort(p.begin(), p.end(), c);
   // std::cout << "min coord "<< p[0] <<"\n";
    for(int i=1; i<5; i++){
     // std::cout << "other "<< p[i] <<"\n";
      p[i] -= p[0];
    }
    p[0] << 0, 0;
    return p;
  }
};

//ペントミノのパターン
struct Pentominos{
  using Vec2i = Eigen::Vector2i;

  std::vector<Pentomino> pieces;

  Pentominos(){
    pieces.resize(12);
    create();
  }

private:
  //全てのペントミノ12個を生成（重複解対策で1つピースを固定している）
  void create(){
    std::vector<Vec2i> p(5);

    p[0] << 0, 0; p[1] << 1, -2; p[2] << 1, -1; p[3] << 1, 0; p[4] << 2, -1;
    pieces[0].setCoords(p);
    pieces[0].setPattern(8);
    pieces[0].setColor(40);

    //pieces[0].setPattern(4);

    p[0] << 0, 0; p[1] << 0, 1; p[2] << 0, 2; p[3] << 0, 3; p[4] << 0, 4;
    pieces[1].setCoords(p);
    pieces[1].setPattern(2);
    pieces[1].setColor(27);

    p[0] << 0, 0; p[1] << 0, 1; p[2] << 0, 2; p[3] << 0, 3; p[4] << 1, 0;
    pieces[2].setCoords(p);
    pieces[2].setPattern(8);
    pieces[2].setColor(58);

    //pieces[2].setPattern(4);


    p[0] << 0, 0; p[1] << 0, 1; p[2] << 0, 2; p[3] << 1, 2; p[4] << 1, 3;
    pieces[3].setCoords(p);
    pieces[3].setPattern(8);
    pieces[3].setColor(9);

    //pieces[3].setPattern(4);


    p[0] << 0, 0; p[1] << 0, 1; p[2] << 0, 2; p[3] << 1, 1; p[4] << 1, 2;
    pieces[4].setCoords(p);
    pieces[4].setPattern(8);
    pieces[4].setColor(86);

    //pieces[4].setPattern(4);

    p[0] << 0, 0; p[1] << 1, -2; p[2] << 1, -1; p[3] << 1, 0; p[4] << 2, 0;
    pieces[5].setCoords(p);
    pieces[5].setPattern(4);
    pieces[5].setColor(196);

    p[0] << 0, 0; p[1] << 0, 1; p[2] << 1, 0; p[3] << 2, 0; p[4] << 2, 1;
    pieces[6].setCoords(p);
    pieces[6].setPattern(4);
    pieces[6].setColor(214);

    p[0] << 0, 0; p[1] << 0, 1; p[2] << 0, 2; p[3] << 1, 0; p[4] << 2, 0;
    pieces[7].setCoords(p);
    pieces[7].setPattern(4);
    pieces[7].setColor(165);

    p[0] << 0, 0; p[1] << 0, 1; p[2] << 1, -1; p[3] << 1, 0; p[4] << 2, -1;
    pieces[8].setCoords(p);
    pieces[8].setSP(2);
    pieces[8].setPattern(1);
    pieces[8].setColor(190);

    //pieces[8].setPattern(4);

    p[0] << 0, 0; p[1] << 1, -1; p[2] << 1, 0; p[3] << 1, 1; p[4] << 2, 0;
    pieces[9].setCoords(p);
    pieces[9].setPattern(1);
    pieces[9].setColor(105);

    p[0] << 0, 0; p[1] << 1, -2; p[2] << 1, -1; p[3] << 1, 0; p[4] << 1, 1;
    pieces[10].setCoords(p);
    pieces[10].setPattern(8);
    pieces[10].setColor(10);

    //pieces[10].setPattern(4);

    p[0] << 0, 0; p[1] << 1, -2; p[2] << 1, -1; p[3] << 1, 0; p[4] << 2, -2;
    pieces[11].setCoords(p);
    pieces[11].setSP(1);
    pieces[11].setPattern(4);
    pieces[11].setColor(227);

    //pieces[11].setPattern(2);

  }
};
#endif
