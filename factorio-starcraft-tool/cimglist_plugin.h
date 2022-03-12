
CImgList(CImgList<T>&& other) : _width(0), _allocated_width(0), _data(nullptr) {
  swap(other);
}

CImgList<T> operator=(CImgList<T>&& other) {
  swap(other);
}
