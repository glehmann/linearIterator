#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkCommand.h"
#include "itkSimpleFilterWatcher.h"

#include "itkImageLinearConstIterator.h"


int main(int, char * argv[])
{
  const int dim = 2;
  
  typedef unsigned char PType;
  typedef itk::Image< PType, dim > IType;

  typedef itk::ImageFileReader< IType > ReaderType;
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName( argv[1] );

  IType::Pointer image = reader->GetOutput();
  image->Update();
  image->DisconnectPipeline();


  typedef itk::ImageLinearConstIterator<IType> IteratorType;
  IteratorType it(image, image->GetLargestPossibleRegion());
  it.SetDirection(1);
  it.GoToBegin();
  while (! it.IsAtEnd() )
    {
    while (! it.IsAtEndOfLine() )
      {
      PType value = it.Get();
      std::cout << (int)value << std::endl;
      ++it;
      }
    it.NextLine();
    }

//   typedef itk::ImageFileWriter< IType > WriterType;
//   WriterType::Pointer writer = WriterType::New();
//   writer->SetInput( reader->GetOutput() );
//   writer->SetFileName( argv[2] );
//   writer->Update();

  return 0;
}

