from setuptools import setup, find_packages

setup(
  name="ps_library",
  version="0.1.0",
  packages=find_packages(),
  install_requires=[
    'online-judge-verify-helper',
    # 依存パッケージ
  ],
  author="kennent",
  description="Problem solving library",
  url="https://github.com/kennent/ps_library",
)
