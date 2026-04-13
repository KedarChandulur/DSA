#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>

template <typename T>
class Flat2DArray
{
public:
	Flat2DArray(const size_t _rowsCount, const size_t _colsCount);
	Flat2DArray();
	~Flat2DArray() = default;

	/*
	*  1. Reserve won't initialize the values(like resize),
	*  it only allocates memory to hold the elements of
	*  (newRowCount * newColCount) elements.
	*  2. You can pass either old row or
	*  old col to only account for one dimension.
	*  3. Also updates row and col count.
	*  4. forceErase clear the entire array.
	*/
	void UpdateAndReserve(const size_t newRowCount, const size_t newColCount, bool forceErase = false);

	/*
	*  1. Resize will initialize the values, default
	*  initializes about (newRowCount * newColCount) elements.
	*  2. You can pass either old row or
	*  old col to only account for one dimension update.
	*  3. Also updates row and col count.
	*  4. forceErase clear the entire array.
	*/
	void UpdateAndResize(const size_t newRowCount, const size_t newColCount, bool forceErase = false);

	size_t GetRowCount() const;
	size_t GetColCount() const;

	size_t GetCurrentSize() const;
	size_t GetCapacity() const;

	void Push_Back(const T& other);

	template<typename... Args>
	void Emplace_Back(Args&&... args);

	/*
	*  Don't call this on an empty vector.
	*/
	T& Back();
	/*
	*  Don't call this on an empty vector.
	*/
	T& Front();

	/*
	*  Don't call this on an empty vector.
	*/
	const T& Back() const;
	/*
	*  Don't call this on an empty vector.
	*/
	const T& Front() const;

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	void Set(const size_t rowIndex, const size_t colIndex, const T& other);

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	template<typename... Args>
	void Emplace(const size_t rowIndex, const size_t colIndex, Args&&... args);

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	void Set(const size_t flatIndex, const T& other);

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	template<typename... Args>
	void Emplace(const size_t flatIndex, Args&&... args);

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	T& operator()(std::size_t rowIndex, std::size_t colIndex);

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	const T& operator()(std::size_t rowIndex, std::size_t colIndex) const;

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	T& at(std::size_t rowIndex, std::size_t colIndex);

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	const T& at(std::size_t rowIndex, std::size_t colIndex) const;

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	T& at(const size_t flatIndex);

	/*
	*  Make sure you access elements which are initialized.
	*  if you reserved memory then your elements might be
	*  in uninitialized state if you are called it for the 1st time.
	*/
	const T& at(const size_t flatIndex) const;

	size_t GetFlatIndex(const size_t rowIndex, const size_t colIndex) const;

	bool IsEmpty() const;

	void RunDemo();

private:
	enum class InputType : int
	{
		ReserveRows = 1,
		ReserveCols = 2,
		PushBack = 3,
		AccessBack = 4,
		AccessFront = 5,
		Print = 6,
		ResizeRows = 7,
		ResizeCols = 8,
		InsertPos = 9,
		AccessPos = 10,
		PrintSize = 11,
		PrintCapacity = 12,
		ReserveRC = 13,
		ResizeRC = 14,
		UpdateFront = 15,
		UpdateBack = 16
	};

private:
	std::vector<T> dataArr;
	size_t rows;
	size_t cols;
};

template<typename T>
inline Flat2DArray<T>::Flat2DArray(const size_t _rowsCount, const size_t _colsCount)
	: rows(_rowsCount), cols(_colsCount)
{
}

template<typename T>
inline Flat2DArray<T>::Flat2DArray()
	: rows(0), cols(0)
{

}

template<typename T>
inline void Flat2DArray<T>::UpdateAndReserve(const size_t newRowCount, const size_t newColCount, bool forceErase)
{
	this->rows = newRowCount;
	this->cols = newColCount;

	const size_t newCapacity = this->rows * this->cols;

	dataArr.reserve(newCapacity);

	if (forceErase)
	{
		dataArr.clear();
	}
}

template<typename T>
inline void Flat2DArray<T>::UpdateAndResize(const size_t newRowCount, const size_t newColCount, bool forceErase)
{
	this->rows = newRowCount;
	this->cols = newColCount;

	const size_t newSize = this->rows * this->cols;

	if (forceErase)
	{
		dataArr.clear();
	}

	dataArr.resize(newSize);
}

template<typename T>
inline size_t Flat2DArray<T>::GetRowCount() const
{
	return rows;
}

template<typename T>
inline size_t Flat2DArray<T>::GetColCount() const
{
	return cols;
}

template<typename T>
inline size_t Flat2DArray<T>::GetCurrentSize() const
{
	return dataArr.size();
}

template<typename T>
inline size_t Flat2DArray<T>::GetCapacity() const
{
	return dataArr.capacity();
}

template<typename T>
inline void Flat2DArray<T>::Push_Back(const T& other)
{
	if (dataArr.size() == dataArr.capacity())
	{
		/*
		*  Array is full...
		*  Increasing row and col by one...
		*  Increasing the capacity.
		*/

		UpdateAndReserve(this->rows + 1, this->cols + 1);
	}

	dataArr.push_back(other);
}

template<typename T>
template<typename... Args>
inline void Flat2DArray<T>::Emplace_Back(Args&&... args)
{
	if (dataArr.size() == dataArr.capacity())
	{
		/*
		*  Array is full...
		*  Increasing row and col by one...
		*  Increasing the capacity.
		*/
		 
		UpdateAndReserve(this->rows + 1, this->cols + 1);
	}

	dataArr.emplace_back(std::forward<Args>(args)...);
}

template<typename T>
inline T& Flat2DArray<T>::Back()
{
	return dataArr.back();
}

template<typename T>
inline T& Flat2DArray<T>::Front()
{
	return dataArr.front();
}

template<typename T>
inline const T& Flat2DArray<T>::Back() const
{
	return dataArr.back();
}

template<typename T>
inline const T& Flat2DArray<T>::Front() const
{
	return dataArr.front();
}

template<typename T>
inline void Flat2DArray<T>::Set(const size_t rowIndex, const size_t colIndex, const T& other)
{
	dataArr[GetFlatIndex(rowIndex, colIndex)] = other;
}

template<typename T>
template<typename... Args>
inline void Flat2DArray<T>::Emplace(const size_t rowIndex, const size_t colIndex, Args&&... args)
{
	dataArr[GetFlatIndex(rowIndex, colIndex)] = T(std::forward<Args>(args)...);
}

template<typename T>
inline void Flat2DArray<T>::Set(const size_t flatIndex, const T& other)
{
	dataArr[flatIndex] = other;
}

template<typename T>
template<typename... Args>
inline void Flat2DArray<T>::Emplace(const size_t flatIndex, Args&&... args)
{
	dataArr[flatIndex] = T(std::forward<Args>(args)...);
}

template<typename T>
inline T& Flat2DArray<T>::operator()(std::size_t rowIndex, std::size_t colIndex)
{
	return dataArr[GetFlatIndex(rowIndex, colIndex)];
}

template<typename T>
inline const T& Flat2DArray<T>::operator()(std::size_t rowIndex, std::size_t colIndex) const
{
	return dataArr[GetFlatIndex(rowIndex, colIndex)];
}

template<typename T>
inline T& Flat2DArray<T>::at(std::size_t rowIndex, std::size_t colIndex)
{
	const size_t flatIndex = GetFlatIndex(rowIndex, colIndex);

	if (flatIndex >= dataArr.size())
		throw std::out_of_range("Flat2DArray::at — index ("
			+ std::to_string(rowIndex) + ", "
			+ std::to_string(colIndex) + ") out of range. Size: "
			+ std::to_string(dataArr.size()));

	return dataArr[flatIndex];
}

template<typename T>
inline const T& Flat2DArray<T>::at(std::size_t rowIndex, std::size_t colIndex) const
{
	const size_t flatIndex = GetFlatIndex(rowIndex, colIndex);

	if (flatIndex >= dataArr.size())
		throw std::out_of_range("Flat2DArray::at — index ("
			+ std::to_string(rowIndex) + ", "
			+ std::to_string(colIndex) + ") out of range. Size: "
			+ std::to_string(dataArr.size()));

	return dataArr[flatIndex];
}

template<typename T>
inline T& Flat2DArray<T>::at(const size_t flatIndex)
{
	if (flatIndex >= dataArr.size())
		throw std::out_of_range("Flat2DArray::at — flat index "
			+ std::to_string(flatIndex) + " out of range. Size: "
			+ std::to_string(dataArr.size()));

	return dataArr[flatIndex];
}

template<typename T>
inline const T& Flat2DArray<T>::at(const size_t flatIndex) const
{
	if (flatIndex >= dataArr.size())
		throw std::out_of_range("Flat2DArray::at — flat index "
			+ std::to_string(flatIndex) + " out of range. Size: "
			+ std::to_string(dataArr.size()));

	return dataArr[flatIndex];
}

template<typename T>
inline size_t Flat2DArray<T>::GetFlatIndex(const size_t rowIndex, const size_t colIndex) const
{
	return rowIndex * cols + colIndex;
}

template<typename T>
inline bool Flat2DArray<T>::IsEmpty() const
{
	return dataArr.empty();
}

template <typename T>
inline void Flat2DArray<T>::RunDemo()
{
	std::cout << "Enter your queries count: (Example: 20)\n";

	int querySize;

	std::cin >> querySize;

	std::cout << "\n";

	for (int query = 1; query <= querySize; ++query)
	{
		std::cout << "Enter your query no: " << query << "\n\n";
		
		std::cout << "Use number: 1 Reserve Rows\n";
		std::cout << "            2 Reserve Cols\n";
		std::cout << "            3 Push Back\n";
		std::cout << "            4 Access Back Ele\n";
		std::cout << "            5 Access Front Ele\n";
		std::cout << "            6 Print all ele\n";
		std::cout << "            7 Resize Rows\n";
		std::cout << "            8 Resize Cols\n";
		std::cout << "            9 Insert at Pos\n";
		std::cout << "           10 Access at Pos\n";
		std::cout << "           11 Print size\n";
		std::cout << "           12 Print Capacity\n";
		std::cout << "           13 Reserve RC\n";
		std::cout << "           14 Resize RC\n";
		std::cout << "           15 Update Front\n";
		std::cout << "           16 Update Back\n\n";

		int type;
		std::cin >> type;
		std::cout << "\n";

		const InputType inputType = static_cast<InputType>(type);

		T value{};
		size_t rowPos = 0;
		size_t colPos = 0;

		size_t rowCount;
		size_t colCount;
		bool forceErase;

		switch (inputType)
		{
			case InputType::ReserveRows:
				std::cout << "Answer 0 to use current row.";
				std::cout << "\nEnter the no of rows to reserve: ";

				rowCount = 0;
				std::cin >> rowCount;

				std::cout << "\nPress 1 to force erase, 0 to do nothing: ";

				forceErase = false;
				std::cin >> forceErase;

				if (rowCount < 1)
				{
					this->UpdateAndReserve(this->rows, this->cols, forceErase);
				}
				else
				{
					this->UpdateAndReserve(rowCount, this->cols, forceErase);
				}
				
				std::cout << "\nUpdated rows count: " << this->rows;
				std::cout << "\nReserved: " << this->GetCapacity();
				break;

			case InputType::ReserveCols:
				std::cout << "Answer 0 to use current col.";
				std::cout << "\nEnter the no of cols to reserve: ";

				colCount = 0;
				std::cin >> colCount;

				std::cout << "\nPress 1 to force erase, 0 to do nothing: ";

				forceErase = false;
				std::cin >> forceErase;

				if (colCount < 1)
				{
					this->UpdateAndReserve(this->rows, this->cols, forceErase);
				}
				else
				{
					this->UpdateAndReserve(this->rows, colCount, forceErase);
				}

				std::cout << "\nUpdated cols count: " << this->cols;
				std::cout << "\nReserved: " << this->GetCapacity();
				break;

			case InputType::PushBack:
				std::cout << "What do you wanna push: ";
				std::cin >> value;
				this->Emplace_Back(value);
				std::cout << "\nSuccessfully Pushed: " << value;
				break;

			case InputType::AccessBack:
				value = this->Back();
				std::cout << "\nBack value: " << value;
				break;

			case InputType::AccessFront:
				value = this->Front();
				std::cout << "\nFront value: " << value;
				break;

			case InputType::Print:
			{
				const size_t n = dataArr.size();

				std::cout << "\nPrinting Flat 2d array as 2d array(matrix):";

				for (size_t i = 0; i < n; ++i)
				{
					const size_t col = i % this->cols;

					if (col == 0)
					{
						std::cout << "\n";
					}

					std::cout << dataArr[i] << "\t";
				}
			}
				break;

			case InputType::ResizeRows:
				std::cout << "Answer 0 to use current row.";
				std::cout << "\nEnter the no of rows to resize: ";

				rowCount = 0;
				std::cin >> rowCount;

				std::cout << "\nPress 1 to force erase, 0 to do nothing: ";

				forceErase = false;
				std::cin >> forceErase;

				if (rowCount < 1)
				{
					this->UpdateAndResize(this->rows, this->cols, forceErase);
				}
				else
				{
					this->UpdateAndResize(rowCount, this->cols, forceErase);
				}

				std::cout << "\nUpdated rows count: " << this->rows;
				std::cout << "\nCurrent Size: " << this->GetCurrentSize();
				break;

			case InputType::ResizeCols:
				std::cout << "Answer 0 to use current col.";
				std::cout << "\nEnter the no of cols to resize: ";

				colCount = 0;
				std::cin >> colCount;

				std::cout << "\nPress 1 to force erase, 0 to do nothing: ";

				forceErase = false;
				std::cin >> forceErase;

				if (colCount < 1)
				{
					this->UpdateAndResize(this->rows, this->cols, forceErase);
				}
				else
				{
					this->UpdateAndResize(this->rows, colCount, forceErase);
				}

				std::cout << "\nUpdated cols count: " << this->cols;
				std::cout << "\nCurrent Size: " << this->GetCurrentSize();
				break;

			case InputType::InsertPos:
				std::cout << "\nEnter the row index: ";

				rowPos = 0;
				std::cin >> rowPos;

				std::cout << "\nEnter the col index: ";

				colPos = 0;
				std::cin >> colPos;

				std::cout << "\nEnter the value to insert: ";
				std::cin >> value;

				if (GetFlatIndex(rowPos, colPos) > this->GetCurrentSize())
				{
					std::cout << "\nInvalid index...";
				}
				else
				{
					this->Emplace(rowPos, colPos, value);
				}

				break;

			case InputType::AccessPos:
				std::cout << "\nEnter the row index: ";

				rowPos = 0;
				std::cin >> rowPos;

				std::cout << "\nEnter the col index: ";

				colPos = 0;
				std::cin >> colPos;

				if (GetFlatIndex(rowPos, colPos) > this->GetCurrentSize())
				{
					std::cout << "\nInvalid index...";
				}
				else
				{
					std::cout << this->at(rowPos, colPos);
				}

				break;

			case InputType::PrintSize:
				std::cout << "\nSize: " << this->GetCurrentSize() << "\n";
				break;

			case InputType::PrintCapacity:
				std::cout << "\nCapacity: " << this->GetCapacity() << "\n";
				break;

			case InputType::ReserveRC:
				std::cout << "Answer 0 to use current row / current col.";
				std::cout << "\nEnter the no of rows to reserve: ";

				rowCount = 0;
				std::cin >> rowCount;

				std::cout << "\nEnter the no of cols to reserve: ";

				colCount = 0;
				std::cin >> colCount;

				std::cout << "\nPress 1 to force erase, 0 to do nothing: ";

				forceErase = false;
				std::cin >> forceErase;

				if (rowCount < 1)
				{
					rowCount = this->rows;
				}

				if (colCount < 1)
				{
					colCount = this->cols;
				}

				this->UpdateAndReserve(rowCount, colCount, forceErase);

				std::cout << "\nUpdated rows count: " << this->rows;
				std::cout << "\nUpdated cols count: " << this->cols;
				std::cout << "\nReserved: " << this->GetCapacity();
				break;

			case InputType::ResizeRC:
				std::cout << "Answer 0 to use current row / current col.";
				std::cout << "\nEnter the no of rows to resize: ";

				rowCount = 0;
				std::cin >> rowCount;

				std::cout << "\nEnter the no of cols to resize: ";

				colCount = 0;
				std::cin >> colCount;

				std::cout << "\nPress 1 to force erase, 0 to do nothing: ";

				forceErase = false;
				std::cin >> forceErase;

				if (rowCount < 1)
				{
					rowCount = this->rows;
				}

				if (colCount < 1)
				{
					colCount = this->cols;
				}

				this->UpdateAndResize(rowCount, colCount, forceErase);

				std::cout << "\nUpdated rows count: " << this->rows;
				std::cout << "\nUpdated cols count: " << this->cols;
				std::cout << "\nCurrent Size: " << this->GetCurrentSize();
				break;

			case InputType::UpdateFront:
				std::cout << "\nCurrent front: " << this->Front();

				std::cout << "\nEnter value to be updated at front: ";

				std::cin >> value;

				this->Front() = value;

				std::cout << "\nCurrent front: " << this->Front();

				break;

			case InputType::UpdateBack:
				std::cout << "\nCurrent back: " << this->Back();

				std::cout << "\nEnter value to be updated at back: ";

				std::cin >> value;

				this->Back() = value;

				std::cout << "\nCurrent back: " << this->Back();
				break;

			default:
				std::cout << "Invalid query, enter your query again...";
				--query;
				break;
		}

		std::cout << "\n\n";
	}
}